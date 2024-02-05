/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:23:54 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/05 17:27:03 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_pipe(t_list *list, char *path, char **args, int saved_stdin, int saved_stdout, t_env4mini *all)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (setup_redirection (list->next) == 1)
			return ;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid)
	{
		close(pipe_fd[1]); // Chiudi lato di scrittura della pipe nel padre
		dup2(pipe_fd[0], STDIN_FILENO); // Collega STDIN alla pipe
		close(pipe_fd[0]); // Chiudi lato di lettura della pipe nel padre
		waitpid(pid, &status, 0);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		free_all(path, args);
	}
	else
	{
		close(pipe_fd[0]); // Chiudi lato di lettura della pipe nel figlio
		dup2(pipe_fd[1], STDOUT_FILENO); // Collega STDOUT alla pipe
		close(pipe_fd[1]); // Chiudi lato di scrittura della pipe nel figlio
		// execve(path, (char *const *)args, all->env);
		// perror("execve");
		
		exit(1);
	}
}

t_list	*forking(t_list *list, pid_t pid, int status, char *path, char **args, int saved_stdin, int saved_stdout, t_env4mini *all)
{
	pid = fork();
	if (pid)
	{
		waitpid(-1, &status, WUNTRACED);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		free_all(path, args);
		list = list->next;
	}
	else
	{
		execve(path, (char *const *)args, all->env);
		perror("execve");
		exit(1);
	}
	return (list);
}

void	while_exe(t_list *list, char *path, char**args, int saved_stdin, int saved_stdout, pid_t pid, int status, t_env4mini *all, int i)
{
	while (list) 
	{
		if (setup_redirection (list) == 1)
			return ;
		init_vars(&path, &args, &i);
		if (list->type != WORD && list->type != PIPE)
			i++;
		if (check_mtx(list, path, args, i) == 1)
			return ;
		strcat(path, list->mtx[i]);
		args = fill_args(list, args, i);
		if (list->type == PIPE)
		{
			handle_pipe(list, path, args, saved_stdin, saved_stdout, all);
			list = list->next;
			continue ;
		}
		list = forking(list, pid, status, path, args, saved_stdin, saved_stdout, all);
	}
}

void	exe(t_list *list, t_env4mini *all)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**args;
	int		i;
	int		saved_stdout;
	int		saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (check_error_redirection(list) == 0)
		while_exe(list, path, args, saved_stdin, saved_stdout, pid, status, all, i);
	close(saved_stdout);
	close(saved_stdin);
}

