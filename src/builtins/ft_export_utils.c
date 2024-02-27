/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:17:04 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/27 09:36:59 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*gestire export var++=value
primo valore di nome var non deve essere un numero
export concatenati*/

#include "../../include/minishell.h"

void	ft_setenv(char *name, char *value, t_env4mini *all)
{
	int		i;
	char	*temp;

	i = 0;
	while (all->env[i])
	{
		if (ft_strncmp(all->env[i], name, ft_strlen(name)) == 0)
		{
			temp = all->env[i];
			all->env[i] = ft_strjoin(name, "=");
			free(temp);
			temp = all->env[i];
			all->env[i] = ft_strjoin(all->env[i], value);
			free(temp);
			return ;
		}
		i++;
	}
	temp = all->env[i];
	all->env[i] = ft_strjoin(name, "");
	free(temp);
	temp = all->env[i];
	all->env[i] = ft_strjoin(all->env[i], value);
	free(temp);
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
