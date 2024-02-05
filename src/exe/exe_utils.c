/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/05 17:46:35 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_error_redirection(t_list *list)
{
	while (list)
	{
		if (list->type != WORD && check_type(list->mtx[0]) != WORD)
		{
			printf("parse error near '%s'\n", list->mtx[0]);
			return (1);
		}
		else if (ft_strcmp(list->mtx[0], "\n") == 0 || ft_strcmp(list->mtx[0], " ") == 0 || ft_strcmp(list->mtx[0], "") == 0)
		{
			printf("parse error near '%s'\n", list->mtx[0]);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int setup_redirection(t_list *list)
{
	while (list)
	{
		if (list->type != WORD && list->type != PIPE)
			redirections(list);
		else if (list->type == PIPE)
			return (0);
		list = list->next;
	}
	return (0);
}

void	init_vars(char **path, char ***args, int *i)
{
	*path = malloc (sizeof(char) * 50);
	*args = malloc (sizeof(char *) * 50);
	*i = 0;
	strcpy(*path, "/bin/");
}

char	**fill_args(t_list *list, char **args, int i)
{
	int j;
	
	j = 0;
	while (list->mtx[i])
		{
			args[j] = malloc (sizeof(char) * 50);
			strcpy(args[j], list->mtx[i]);
			i++;
			j++;
		}
	args[j] = NULL;
	return (args);
}

int	check_mtx(t_list *list, char *path, char **args, int i)
{
	if (!list->mtx[i])
	{
		free_all(path, args);
		return (1);
	}
	return (0);
}

/*original exe
void exe(t_list *list, t_env4mini *all)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**args;
	int		i;
	int		j;
	int		saved_stdout;
	int		saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	setup_redirection (list);
	while (list) 
	{
		path = malloc (sizeof(char) * 50);
		args = malloc (sizeof(char *) * 50);
		i = 0;
		j = 0;
		strcpy(path, "/bin/");
		if (list->type != WORD && check_type(list->mtx[i]) != WORD)
		{
			printf("parse error near '%s'\n", list->mtx[i]);
			return ;
		}
		if (list->type != WORD && list->type != PIPE)
		{
			i++;
		}
		else if (list->type == PIPE)
		{
			handle_pipe(list, all);
			list = list->next;
			continue ;
		}
		if (!list->mtx[i])
		{
			free_all(path, args);
			return ;
		}
		strcat(path, list->mtx[i]);
		while (list->mtx[i])
		{
			args[j] = malloc (sizeof(char) * 50);
			strcpy(args[j], list->mtx[i]);
			i++;
			j++;
		}
		args[j] = NULL;
		
		pid = fork();
		if (pid) {
			waitpid(-1, &status, WUNTRACED);
			dup2(saved_stdout, STDOUT_FILENO);
			dup2(saved_stdin, STDIN_FILENO);
			list = list->next;
			free_all(path, args);
		}
		else
		{
			execve(path, (char *const *)args, all->env);
			perror("execve");
			exit(1);
		}
	}
	close(saved_stdout);
	close(saved_stdin);
}*/
