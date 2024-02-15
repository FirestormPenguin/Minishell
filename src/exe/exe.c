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
		waitpid(proc->pid, &(proc->status), 0);
		dup2(proc->saved_stdout, STDOUT_FILENO);
		dup2(proc->saved_stdin, STDIN_FILENO);
		free_all_generic(proc->path, proc->args);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		exit(1);
	}
}

static int scroll_list_in_while(t_list *list, t_process *proc)
{
	reset_stdin_stdout(proc);
	if (list != NULL)
		return (1);
	return (0);
}

t_list	*forking(t_list *list, t_process *proc)
{
	proc->pid = fork();
	if (proc->pid)
	{
		waitpid(-1, &(proc->status), WUNTRACED);
		if (WIFEXITED(proc->status))
			last_exit_code = WEXITSTATUS(proc->status);
		else
			last_exit_code = -1;
		// reset_stdin_stdout(proc);
		free_all_generic(proc->path, proc->args);
		if (list == NULL)
			return (NULL);
		// list = list->next;
	}
	else
	{
		if (access(proc->path, X_OK) == 0)
		{
			execve(proc->path, (char *const *)(proc->args), proc->all->env);
			perror("execve");
			exit(1);
		}
		else
		{
			printf("%s: command not found\n", proc->args[0]);
			exit(127);
		}
	}
	return (list);
}

void	while_exe(t_list *list, t_process *proc, int i)
{
	while (list)
	{
		init_vars(proc, &i, proc->all);
		list = fill_args(list, proc, i);
		strcpy(proc->path, path_finder(proc->args, proc->all));
		if (proc->args && proc->args[i])
			import_builtins(list, proc);
		if (scroll_list_in_while(list, proc))
			list = list->next;
		else
			break;
	}
}

void	exe(t_list *list, t_env4mini *all)
{
	t_process	proc;
	int			i;

	i = 0;
	proc.saved_stdout = dup(STDOUT_FILENO);
	proc.saved_stdin = dup(STDIN_FILENO);
	proc.all = all;
	if (check_error_redirection(list) == 0 && setup_redirection(list, &proc) == 0)
		while_exe(list, &proc, i);
	close(proc.saved_stdout);
	close(proc.saved_stdin);
}
