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

void	pipe_forking(t_list *list, t_process *proc)
{
	int		pid;
	int		pipe_fd[2];
	int		status;

	pipe(pipe_fd);
	pid = fork();
	if (pid)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, &status, 0);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		exit(1);
	}
}

void	forking(t_list *list, t_process *proc)
{
	proc->pid = fork();
	if (proc->pid)
	{
		waitpid(-1, &(proc->status), WUNTRACED);
		if (WIFEXITED(proc->status))
			last_exit_code = WEXITSTATUS(proc->status);
		else
			last_exit_code = -1;
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
}

void	write_on_output(t_list *list, t_process *proc)
{
	int		input_fd;
	char	c;

	input_fd = open("746d70_1", O_RDONLY);
	while (read(input_fd, &c, 1) > 0)
		write (STDOUT_FILENO, &c, 1);
	close(input_fd);
}

/*questo serve per le redirection in output, non in input,
per input si usa setup_redirection come prima*/
void stream_output(t_list *list, t_process *proc)
{
	int	count;

	count = 0;
	reset_stdin_stdout(proc);
	while (list)
	{
		if (list->type == OUT && list->mtx[0])
		{
			output(list->mtx[0], proc);
			count++;
			write_on_output(list, proc);
		}
		else if (list->type == DOUBLE_OUT && list->mtx[0])
		{
			append(list->mtx[0], proc);
			count++;
			write_on_output(list, proc);
		}
		list = list->next;
		if (list == NULL || list->type == PIPE)
			break;
	}
	if (count == 0)
		write_on_output(list, proc);
	return ;
}

void	while_exe(t_list *list, t_process *proc, int i)
{
	t_list	*tmp_list;

	while (list)
	{
		init_vars(proc, &i, proc->all);
		output("746d70_1", proc);
		tmp_list = list;
		if (list->type == PIPE)
		{
			input("746d70_1", proc);
			list = fill_args_pipe(list, proc, i);
		}
		else
			list = fill_args(list, proc, i);
		setup_redirection(list, proc);
		strcpy(proc->path, path_finder(proc->args, proc->all));
		if (proc->args && proc->args[i] && import_builtins(list, proc))
			;
		stream_output(tmp_list, proc);
		reset_stdin_stdout(proc);
		free_all_generic(proc->path, proc->args);
	}
	if (access("746d70_1", F_OK) != -1)
		unlink("746d70_1");
}

void	exe(t_list *list, t_env4mini *all)
{
	t_process	proc;
	int			i;

	i = 0;
	proc.saved_stdout = dup(STDOUT_FILENO);
	proc.saved_stdin = dup(STDIN_FILENO);
	proc.all = all;
	if (check_error_redirection(list) == 0)
		while_exe(list, &proc, i);
	close(proc.saved_stdout);
	close(proc.saved_stdin);
}
