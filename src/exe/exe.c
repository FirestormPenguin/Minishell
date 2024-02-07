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

//ogni funzione deve avere al massimo 4 argomenti brudda :_)
//non sono cazzi miei >:(
//risolti i non-cazzi-tuoi ;)

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

t_list	*forking(t_list *list, t_process *proc)
{
	proc->pid = fork();
	if (proc->pid)
	{
		waitpid(-1, &(proc->status), WUNTRACED);
		dup2(proc->saved_stdout, STDOUT_FILENO);
		dup2(proc->saved_stdin, STDIN_FILENO);
		free_all_generic(proc->path, proc->args);
		list = list->next;
	}
	else
	{
		execve(proc->path, (char *const *)(proc->args), proc->all->env);
		perror("execve");
		exit(1);
	}
	return (list);
}

void	while_exe(t_list *list, t_process *proc, int i)
{
	while (list) 
	{
		init_vars(&(proc->path), &(proc->args), &i);
		if (list->type != WORD && list->type != PIPE)
			i++;
		if (check_mtx(list, proc->path, proc->args, i) == 1)
			return ;
		strcat(proc->path, list->mtx[i]);
		proc->args = fill_args(list, proc->args, i);
		if (proc->args && proc->args[0]) {
			if (ft_strcmp(proc->args[0], "exit") == 0) {
				ft_exit(proc->args);
				return;
			}
			else if (ft_strcmp(proc->args[0], "echo") == 0) {
				ft_echo(proc->args);
				return;
			}
		}
		list = forking(list, proc);
	}
}

void	exe(t_list *list, t_env4mini *all)
{
	t_process proc;
	int		i;

	proc.saved_stdout = dup(STDOUT_FILENO);
	proc.saved_stdin = dup(STDIN_FILENO);
	proc.all = all;
	if (check_error_redirection(list) == 0 && setup_redirection(list) == 0)
		while_exe(list, &proc, i);
	close(proc.saved_stdout);
	close(proc.saved_stdin);
}
