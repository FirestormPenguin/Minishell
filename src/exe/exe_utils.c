/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/26 11:19:50 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pipe_at_first(t_list *list, int flag)
{
	if (list->type == PIPE && flag == 0)
	{
		printf("parse error near '|'\n");
		return (1);
	}
	return (0);
}

void	parse_error_gen(t_list *list)
{
	char	*s;
	
	s = malloc(sizeof(char) * 5);
	if (list->next)
	{
		if (list->next->type == IN)
			s = "<";
		else if (list->next->type == OUT)
			s = ">";
		else if (list->next->type == DOUBLE_OUT)
			s = ">>";
		else if (list->next->type == HERE_DOC)
			s = "<<";
	}
	printf("parse error near '%s'\n", s);
}

int	check_error_redirection(t_list *list)
{
	int		flag;

	flag = 0;
	while (list)
	{
		if (check_pipe_at_first(list, flag) == 1)
			return (1);
		flag = 1;
		if (list->next)
		{
			if (list->type == PIPE && list->next->type != WORD && list->next->type != PIPE && list->next->mtx)
			{
				list = list->next;
				continue ;
			}
			else if (list->type != WORD && list->type != PIPE && !list->mtx && list->next->type != WORD)
			{
				parse_error_gen(list);
				return (1);
			}
		}
		else if (list->type != WORD && !list->next && !list->mtx)
		{
			parse_error_gen(list);
			return (1);
		}
		else if (ft_strcmp(list->mtx[0], "\n") == 0
			|| ft_strcmp(list->mtx[0], " ") == 0
			|| ft_strcmp(list->mtx[0], "") == 0)
		{
			parse_error_gen(list);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int	setup_redirection(t_list *list, t_process *proc)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->type != WORD && list->type != PIPE)
		{
			redirections(list, proc);
			count++;
		}
		list = list->next;
		if (list == NULL || list->type == PIPE)
			break ;
	}
	if (count > 0)
		return (1);
	return (0);
}

char	*ft_getenv(char *name, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	if (name == NULL || env == NULL)
	{
		printf("name or env is NULL\n");
		return (NULL);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	*path_finder(char **cmd, t_env4mini *all)
{
	int		i;
	char	*path;
	char	**paths;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp2 = ft_getenv("PATH", all->env);
	paths = ft_split(tmp2, ':');
	tmp = NULL;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!cmd)
			break ;
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_double_pointer(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_double_pointer(paths);
	if (!cmd)
		return (NULL);
	return (ft_strdup(cmd[0]));
}
