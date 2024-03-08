/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:33:36 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/08 00:33:36 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(char *key, t_env4mini *all)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (all->env[i] != NULL)
	{
		if (ft_strncmp(all->env[i], key, key_len) == 0
			&& all->env[i][key_len] == '=')
			return (all->env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	check_cd_home(char **args, char *home)
{
	if (home == NULL || chdir(home) == -1)
	{
		args[1] = home;
		perror("cd");
		return (1);
	}
	return (0);
}

int	check_cd_err(char **args)
{
	if (chdir(args[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[1]);
		return (1);
	}
	return (0);
}

void	update_pwd(t_env4mini *all)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = get_env_value("PWD", all);
	pwd = getcwd(NULL, 0);
	ft_setenv("OLDPWD", oldpwd, all);
	ft_setenv("PWD", pwd, all);
	free(pwd);
}

int	ft_cd(char **args, t_env4mini *all)
{
	char	*home;

	home = get_env_value("HOME", all);
	if (!args[1] || ft_strcmp(args[1], " ") == 0
		|| ft_strcmp(args[1], "") == 0)
	{
		home = get_env_value("HOME", all);
		check_cd_home(args, home);
	}
	else if (args[1] != NULL && !ft_strcmp(args[1], "$HOME"))
	{
		home = get_env_value("HOME", all);
		if (home == NULL || chdir(home) == -1)
		{
			perror("cd");
			return (1);
		}
	}
	else
		if (check_cd_err(args))
			return (1);
	update_pwd(all);
	return (0);
}
