/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:23:54 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/05 16:21:11 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_pipe(t_list *list, t_env4mini *all)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}
	if (pid)
	{
		close(pipe_fd[1]); // Chiudi lato di scrittura della pipe nel padre
		dup2(pipe_fd[0], STDIN_FILENO); // Collega STDIN alla pipe
		close(pipe_fd[0]); // Chiudi lato di lettura della pipe nel padre
		exe(list->next, all);
		waitpid(pid, &status, 0);
	}
	else
	{
		close(pipe_fd[0]); // Chiudi lato di lettura della pipe nel figlio
		dup2(pipe_fd[1], STDOUT_FILENO); // Collega STDOUT alla pipe
		close(pipe_fd[1]); // Chiudi lato di scrittura della pipe nel figlio
		// Esegui il primo comando
		exe(list, all);
		exit(EXIT_SUCCESS);
	}
}

void	init_vars(char **path, char ***args, int *i)
{
	*path = malloc (sizeof(char) * 50);
	*args = malloc (sizeof(char *) * 50);
	*i = 0;
	strcpy(*path, "/bin/");
}

t_list	*forking(t_list *list, pid_t pid, int status, char *path, char **args, int saved_stdin, int saved_stdout, t_env4mini *all)
{
	pid = fork();
	if (pid) {
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

void	while_exe(t_list *list, char *path, char**args, int saved_stdout, int saved_stdin, pid_t pid, int status, t_env4mini *all, int i)
{
	while (list) 
	{
		init_vars(&path, &args, &i);
		if (list->type != WORD && list->type != PIPE)
			i++;
		else if (list->type == PIPE)
		{
			//handle_pipe(list, all);
			list = list->next;
			continue ;
		}
		if (!list->mtx[i])
		{
			free_all(path, args);
			return ;
		}
		strcat(path, list->mtx[i]);
		args = fill_args(list, args, i);
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
	if (setup_redirection (list) == 0)
		while_exe(list, path, args, saved_stdout, saved_stdin, pid, status, all, i);
	close(saved_stdout);
	close(saved_stdin);
}

