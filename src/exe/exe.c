/* ************************************************************************** */
/*                                                                            */
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

void	forking_pipe(t_list *list, t_process *proc, t_list *tmp_list, int pipe_count)
{
	signal(SIGINT, sigint_handle_child);
	signal(SIGQUIT, sigquit_handle_child);

	if (pipe_count)
		pipe(proc->pipe_fd);
	proc->pid = fork();
	if (proc->pid)
	{
		close(proc->saved_fd);
		if (!pipe_count)
		{
			while (waitpid(-1, &(proc->status), WUNTRACED) != -1)
				;
			proc->saved_fd = dup(STDIN_FILENO);
			if (WIFEXITED(proc->status))
				g_last_exit_code = WEXITSTATUS(proc->status);
			else
				g_last_exit_code = -1;
		}
		else
		{
			close(proc->pipe_fd[1]);
			proc->saved_fd = proc->pipe_fd[0];
		}
	}
	else
	{
		int a = setup_redirection(tmp_list, proc);
		if (pipe_count)
		{
			if (a != 1)
			{
				dup2(proc->pipe_fd[1], STDOUT_FILENO);
			}
			close(proc->pipe_fd[1]);
			close(proc->pipe_fd[0]);
		}
		if (check_builtins(list, proc) == 1)
		{
			import_builtins(list, proc);
		}
		else if (check_env_command(list, proc) == 1)
		{
			execute_env_command(list, proc);
		}
		else
		{
			if (access(proc->path, X_OK) == 0)
			{
				if (a != 1)
					dup2(proc->saved_fd, STDIN_FILENO);
				close(proc->saved_fd);
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
		exit (1);
	}
}

void	while_exe_pipe(t_list *list, t_process *proc, int i, int pipe_count)
{
	t_list	*tmp_list;

	proc->saved_fd = dup(STDIN_FILENO);
	while (list)
	{
		init_vars(proc, &i, proc->all);
		tmp_list = list;
		list = fill_args_pipe(list, proc, i);
		strcpy(proc->path, path_finder(proc->args, proc->all));
		forking_pipe(list, proc, tmp_list, pipe_count);
		reset_stdin_stdout(proc);
		free_all_generic(proc->path, proc->args);
		pipe_count--;
	}
}

void	exe(t_list *list, t_env4mini *all)
{
	t_process	proc;
	int			i;
	t_list		*list_h;
	int			pipe_count;

	i = 0;
	pipe_count = 0;
	list_h = list;
	proc.saved_stdout = dup(STDOUT_FILENO);
	proc.saved_stdin = dup(STDIN_FILENO);
	proc.all = all;
	if (check_error_redirection(list) == 0)
	{
		while(list)
		{
			if(list->type == PIPE)
				pipe_count++;
			list = list->next;
		}
		while_exe_pipe(list_h, &proc, i, pipe_count);
	}
	close(proc.saved_stdout);
	close(proc.saved_stdin);
}
