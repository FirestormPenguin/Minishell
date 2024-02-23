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

void	forking(t_list *list, t_process *proc)
{
	signal(SIGINT, sigint_handle_child);
	signal(SIGQUIT, sigquit_handle_child);

	pipe(proc->pipe_fd);
	proc->pid = fork();
	if (proc->pid)
	{
		close (proc->pipe_fd[1]);
		waitpid(-1, &(proc->status), WUNTRACED);
		if (check_builtins(list, proc) == 1)
		{
			import_builtins(list, proc);
		}
		else if (check_env_command(list, proc) == 1)
			execute_env_command(list, proc);
		proc->saved_fd = proc->pipe_fd[0];
		if (WIFEXITED(proc->status))
			g_last_exit_code = WEXITSTATUS(proc->status);
		else
			g_last_exit_code = -1;
	}
	else
	{
		dup2(proc->pipe_fd[1], STDOUT_FILENO);
		close (proc->pipe_fd[1]);
		close (proc->pipe_fd[0]);
		if (check_builtins(list, proc) == 1)
		{
			exit (0);
		}
		else if (check_env_command(list, proc) == 1)
		{
			exit (0);
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
		exit (1);
	}
}

void	forking_pipe(t_list *list, t_process *proc)
{
	signal(SIGINT, sigint_handle_child);
	signal(SIGQUIT, sigquit_handle_child);

	pipe(proc->pipe_fd);
	proc->pid = fork();
	if (proc->pid)
	{
		close (proc->pipe_fd[1]);
		waitpid(-1, &(proc->status), WUNTRACED);
		proc->saved_fd = proc->pipe_fd[0];
		close(proc->pipe_fd[0]);
		if (WIFEXITED(proc->status))
			g_last_exit_code = WEXITSTATUS(proc->status);
		else
			g_last_exit_code = -1;
	}
	else
	{
		dup2(proc->pipe_fd[1], STDOUT_FILENO);
		close (proc->pipe_fd[1]);
		close (proc->pipe_fd[0]);
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

void	write_on_output(t_process *proc)
{
	char	c;

	while (read(proc->saved_fd, &c, 1) > 0)
		write (STDOUT_FILENO, &c, 1);
}

void stream_output(t_list *list, t_process *proc)
{
	int	count;

	count = 0;
	dup2(proc->saved_stdout, STDOUT_FILENO);
	while (list)
	{
		if (list->type == OUT && list->mtx[0])
		{
			output(list->mtx[0], proc);
			count++;
			write_on_output(proc);
		}
		else if (list->type == DOUBLE_OUT && list->mtx[0])
		{
			append(list->mtx[0], proc);
			count++;
			write_on_output(proc);
		}
		list = list->next;
		if (list == NULL)
			break;
		else if (list == NULL || list->type == PIPE)
		{
			break ;
			count++;
		}
	}
	if (count == 0)
		write_on_output(proc);
	return ;
}

void	while_exe(t_list *list, t_process *proc, int i)
{
	t_list	*tmp_list;

	while (list)
	{
		init_vars(proc, &i, proc->all);
		tmp_list = list;
		dup2 (proc->saved_stdin, STDIN_FILENO);
		setup_redirection(list, proc);
		list = fill_args(list, proc, i);
		strcpy(proc->path, path_finder(proc->args, proc->all));
		forking(list, proc);
		stream_output(tmp_list, proc);
		reset_stdin_stdout(proc);
		free_all_generic(proc->path, proc->args);
	}
}

void	while_exe_pipe(t_list *list, t_process *proc, int i)
{
	t_list	*tmp_list;

	while (list)
	{
		init_vars(proc, &i, proc->all);
		tmp_list = list;
		if (list->type == PIPE)
		{
			dup2 (proc->saved_fd, STDIN_FILENO);
			list = fill_args_pipe(list, proc, i);
		}
		else
		{
			dup2 (proc->saved_stdin, STDIN_FILENO);
			list = fill_args(list, proc, i);
		}
		setup_redirection(list, proc);
		strcpy(proc->path, path_finder(proc->args, proc->all));
		forking_pipe(list, proc);
		stream_output(tmp_list, proc);
		reset_stdin_stdout(proc);
		free_all_generic(proc->path, proc->args);
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
		if (pipe_count > 0)
			while_exe_pipe(list_h, &proc, i);
		else
			while_exe(list_h, &proc, i);
	}
	close(proc.saved_stdout);
	close(proc.saved_stdin);
}
