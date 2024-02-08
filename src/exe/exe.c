/* ************************************************************************** */
/*                                                                         */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:23:54 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/07 12:40:31 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_pipe(t_list *list, t_process *proc)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	proc->pid = fork();
	if (proc->pid)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		waitpid(proc->pid, &(proc->status), 0);
		dup2(proc->saved_stdout, STDOUT_FILENO);
		dup2(proc->saved_stdin, STDIN_FILENO);
		free_all_generic(proc->path, proc->args);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(1);
	}
}

void	reset_stdin_stdout(t_process *proc)
{
	dup2(proc->saved_stdout, STDOUT_FILENO);
	dup2(proc->saved_stdin, STDIN_FILENO);
}

t_list	*forking(t_list *list, t_process *proc)
{
	proc->pid = fork();
	if (proc->pid)
	{
		waitpid(-1, &(proc->status), WUNTRACED);
		reset_stdin_stdout(proc);
		free_all_generic(proc->path, proc->args);
		list = list->next;
	}
	else
	{
		if (access(proc->path, X_OK) == 0)
		{
			execve(proc->path, (char *const *)(proc->args), proc->all->env);
			perror("execve");
		}
		else
		{
			printf("%s: command not found\n", proc->args[0]);
		}
		exit(1);
	}
	return (list);
}

/* Debug per ft_cd, ho notato che in create_node nel parser l'array di liste non 
temrinava correttamente con NULL come dovrebbe essere, ra va bene, prima però la built-in
cd si rompeva perché dopo la prima chiamata di funzione e il change directory, in qualsiasi
caso veniva riempito args[1] con un dati compromessi visto che l'array non terminava 
in modo corretto, allora diventava inutilizzabile ogni volta che cercavi di tonrare ad $HOME*/

void	while_exe(t_list *list, t_process *proc, int i)
{
	while (list) 
	{
		init_vars(&(proc->path), &(proc->args), &i);
		if (list->type != WORD && list->type != PIPE)
			i++;
		/*printf("prev proc->path: %s\n", proc->path);
		printf("prev proc->args[1]: %s\n", proc->args[1]);*/
		if (check_mtx(list, proc->path, proc->args, i) == 1)
			return ;
		strcat(proc->path, list->mtx[i]);
		/*printf("proc->path: %s\n", proc->path);
		printf("proc->args[1]: %s\n", proc->args[1]);*/
		proc->args = fill_args(list, proc->args, i);
		if (proc->args && proc->args[0])
		{
			if (ft_strcmp(proc->args[0], "exit") == 0)
			{
				ft_exit(proc->args);
				reset_stdin_stdout(proc);
				list = list->next;
			}
			else if (ft_strcmp(proc->args[0], "echo") == 0)
			{
				ft_echo(proc->args);
				reset_stdin_stdout(proc);
				list = list->next;
			}
			else if (ft_strcmp(proc->args[0], "pwd") == 0)
			{
				ft_pwd();
				reset_stdin_stdout(proc);
				list = list->next;
			}
			else if (ft_strcmp(proc->args[0], "env") == 0)
			{
				ft_env(proc->all->env);
				reset_stdin_stdout(proc);
				list = list->next;
			}
			else if (ft_strcmp(proc->args[0], "cd") == 0 )
			{
				ft_cd(proc->args, proc->all);
				reset_stdin_stdout(proc);
				list = list->next;
			}
			/*else if (ft_strcmp(proc->args[0], "export") == 0)
			{
				ft_export(proc->args, proc->all);
				return;
			}
			else if (ft_strcmp(proc->args[0], "unset") == 0)
			{
				ft_unset(proc->args, proc->all);
				return;
			} */
			else
			{
				list = forking(list, proc);
			}
		}
	}
}

void	exe(t_list *list, t_env4mini *all)
{
	t_process proc;
	int		i;

	i = 0;
	proc.saved_stdout = dup(STDOUT_FILENO);
	proc.saved_stdin = dup(STDIN_FILENO);
	proc.all = all;
	if (check_error_redirection(list) == 0 && setup_redirection(list) == 0)
		while_exe(list, &proc, i);
	close(proc.saved_stdout);
	close(proc.saved_stdin);
}
