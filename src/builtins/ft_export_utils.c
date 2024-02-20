/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:17:04 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/20 02:21:54 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_setenv(char *name, char *value, t_env4mini *all)
{
	int	i;

	i = 0;
	while (all->env[i])
	{
		if (ft_strncmp(all->env[i], name, ft_strlen(name)) == 0)
		{
			all->env[i] = ft_strjoin(name, "=");
			all->env[i] = ft_strjoin(all->env[i], value);
			return ;
		}
		i++;
	}
	all->env[i] = ft_strjoin(name, "=");
	all->env[i] = ft_strjoin(all->env[i], value);
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
			if (i > 0 && str[i - 1] != ' ')
				return (0);
			else
				return (-1);
		}
		i++;
	}
	return (1);
}
