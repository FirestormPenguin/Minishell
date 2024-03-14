/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:17:04 by mivendit          #+#    #+#             */
/*   Updated: 2024/03/14 23:07:05 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*gestire export var++=value
fanculo agli export concatenati*/

#include "../../include/minishell.h"

void	replinenv(char *name, char *value, int i, t_env4mini *all)
{
	char	*joined;

	if (value && *value != '\0')
	{
		joined = ft_strjoin(name, "=");
		all->env[i] = ft_strjoin(joined, value);
		free(joined);
	}
	else
		all->env[i] = ft_strjoin(name, "");
}

void	ft_setenv(char *name, char *value, t_env4mini *all)
{
	int		i;
	int		size;

	i = 0;
	while (all->env[i])
	{
		if (ft_strncmp(all->env[i], name, ft_strlen(name)) == 0)
		{
			free(all->env[i]);
			replinenv(name, value, i, all);
			return ;
		}
		i++;
	}
	replinenv(name, value, i, all);
	size = i + 2;
	all->env = (char **)ft_realloc(all->env, sizeof(char *), i + 1, size);
	if (!all->env)
	{
		printf("all->env in ft_setenv realloc error\n");
		return ;
	}
	all->env[i + 1] = NULL;
}

int	find_valid_equals(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i > 0 && str[i - 1] == '+')
			{
				if ((str[i - 2] == ' ' || str[i - 2] == '+' || !str[i - 2]))
					return (2);
			}
			if ((i > 0 && str[i - 1] != ' '))
				return (0);
			else
				return (-1);
		}
		i++;
	}
	return (1);
}

int	is_valid_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_'
			&& str[i] != '+' && str[i] != '=' )
			return (0);
		i++;
	}
	return (1);
}
