/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/03/15 00:02:27 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_redirection(t_list *list)
{
	int	count;
	int	status;

	count = 0;
	status = 0;
	while (list)
	{
		if (list->type != WORD && list->type != PIPE)
		{
			status |= redirections(list);
			count++;
		}
		list = list->next;
		if (list == NULL || list->type == PIPE)
			break ;
	}
	if (count > 0)
		return (status);
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
		if (ft_strncmp(env[i], name, len) == 0)
		{
			if (env[i][len] == '=')
				return (&env[i][len + 1]);
			return (&env[i][len]);
		}
		i++;
	}
	return (NULL);
}

char	*construct_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!cmd)
		{
			free(tmp);
			break ;
		}
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*path_finder(char **cmd, t_env4mini *all)
{
	char	*tmp2;
	char	**paths;
	char	*result;

	tmp2 = ft_getenv("PATH", all->env);
	paths = ft_split(tmp2, ':');
	result = construct_path(paths, cmd[0]);
	free_double_pointer(paths);
	if (!cmd)
		return (NULL);
	if (result)
		return (result);
	return (ft_strdup(cmd[0]));
}

/*char	*path_finder(char **cmd, t_env4mini *all)
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
		{
			free (tmp);
			break ;
		}
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
}*/
