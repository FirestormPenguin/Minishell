/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:23:54 by egiubell          #+#    #+#             */
/*   Updated: 2024/03/14 23:28:18 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	while_exe(t_list *list, t_process *proc, int i, int pipe_count)
{
	t_list	*tmp_list;

	proc->saved_fd = dup(STDIN_FILENO);
	while (list)
	{
		init_vars(proc, &i);
		tmp_list = list;
		list = fill_args(list, proc, i);
		proc->path = path_finder(proc->args, proc->all);
		forking(list, proc, tmp_list, pipe_count);
		dup2(proc->saved_stdin, STDIN_FILENO);
		dup2(proc->saved_stdout, STDOUT_FILENO);
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
		while (list)
		{
			if (list->type == PIPE)
				pipe_count++;
			list = list->next;
		}
		while_exe(list_h, &proc, i, pipe_count);
	}
	free_list(list_h);
	close(proc.saved_stdout);
	close(proc.saved_stdin);
}
