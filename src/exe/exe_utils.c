/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/12 17:09:26 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_stdin_stdout(t_process *proc)
{
	
	dup2(proc->saved_stdout, STDOUT_FILENO);
	dup2(proc->saved_stdin, STDIN_FILENO);
}

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

int setup_redirection(t_list *list, t_process *proc)
{
	while (list)
	{
		if (list->type != WORD && list->type != PIPE)
			redirections(list, proc);
		else if (list->type == PIPE)
			return (0);
		list = list->next;
	}
	return (0);
}

void free_double_pointer(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char *ft_getenv(char *name, char **env)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(name);
    if (name == NULL || env == NULL) {
        printf("name or env is NULL\n");
        return NULL;
    }

    while (env[i])
    {
        if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
            return (&env[i][len + 1]);
        i++;
    }
    return (NULL);
}

char *path_finder(char **cmd, t_env4mini *all)
{
	int		i;
	char	*path;
	char	**paths;
	char 	*tmp;
	char 	*tmp2;
	char	*absol;

	i = 0;
	absol = ft_calloc(5, sizeof(char *));
	strcpy(absol, "");
	tmp2 = ft_getenv("PATH", all->env);
	paths = ft_split(tmp2, ':');
	tmp = NULL;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_double_pointer(paths);
			free(absol);
			return (path);
		}
		free(path);
		i++;
	}
	free_double_pointer(paths);
	return (absol);
}

void init_vars(t_process *proc, int *i, t_env4mini *all)
{
	char *tmp_args = NULL;

	proc->path = ft_calloc(1000, sizeof(char *));
	proc->args = ft_calloc(50, sizeof(char *));
	*i = 0;
}

t_list *fill_args(t_list *list, t_process *proc, int i)
{
	int j;
	
	j = 0;
	while (list)
	{
		if (list->type == PIPE)
			break;
		i = 0;
		if (list->type != WORD && list->type != PIPE)
			i++;
		if (check_mtx(list, proc, i) == 1)
			return (NULL);
		while (list->mtx[i])
		{
			proc->args[j] = malloc(strlen(list->mtx[i]) + 1);
			if (!proc->args[j])
			{
				perror("malloc failed");
				exit(EXIT_FAILURE);
			}
			strcpy(proc->args[j], list->mtx[i]);
			i++;
			j++;
		}
		list = list->next;
	}
	proc->args[j] = NULL;
	return (list);
}

int	check_mtx(t_list *list, t_process *proc, int i)
{
	if (!list->mtx[i])
	{
		reset_stdin_stdout(proc);
		free_all_generic(proc->path, proc->args);
		return (1);
	}
	return (0);
}

