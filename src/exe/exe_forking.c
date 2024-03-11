/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_forking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:23:54 by egiubell          #+#    #+#             */
/*   Updated: 2024/03/09 14:44:27 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_in_out_pipe(t_process *proc)
{
	if (proc->red_ctrl != 1)
		dup2(proc->pipe_fd[1], STDOUT_FILENO);
	close(proc->pipe_fd[1]);
	proc->saved_fd = proc->pipe_fd[0];
}

int	check_b_e(t_list *list, t_process *proc, int pipe_count)
{
	t_grb_collector	*grb_ptr;

	if (check_builtins(proc))
	{
		close(proc->saved_fd);
		if (pipe_count)
		{
			set_in_out_pipe(proc);
			if (!ft_strncmp(proc->args[0], "cd", 3))
				return (1);
		}
		grb_ptr = set_garbage_collector(list, proc);
		import_builtins(proc, grb_ptr);
		free(grb_ptr);
		return (1);
	}
	else if (check_env_command(proc))
	{
		close(proc->saved_fd);
		if (pipe_count)
			set_in_out_pipe(proc);
		execute_env_command(proc);
		return (1);
	}
	return (0);
}

void	parent(t_process *proc, int pipe_count)
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

void	child(t_process *proc, int pipe_count)
{
	printf("|%d|%d\n", proc->red_ctrl, pipe_count);
	if (pipe_count)
	{
		if (proc->red_ctrl != 1)
			dup2(proc->pipe_fd[1], STDOUT_FILENO);
		close(proc->pipe_fd[1]);
		close(proc->pipe_fd[0]);
	}
	if (access(proc->path, X_OK) == 0)
	{
		if (proc->red_ctrl != 1)
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
	exit(1);
}

void	forking(t_list *list, t_process *proc, t_list *tmp_list, int pipe_count)
{
	signal(SIGINT, sigint_handle_child);
	signal(SIGQUIT, sigquit_handle_child);
	proc->red_ctrl = 0;
	if (pipe_count)
		pipe(proc->pipe_fd);
	proc->red_ctrl = setup_redirection(tmp_list);
	if (!proc->args)
			return ;
	if (check_b_e(list, proc, pipe_count) == 1)
		return ;
	proc->pid = fork();
	if (proc->pid)
		parent(proc, pipe_count);
	else
		child(proc, pipe_count);
}
