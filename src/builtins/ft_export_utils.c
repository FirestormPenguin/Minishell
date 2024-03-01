/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:17:04 by mivendit          #+#    #+#             */
/*   Updated: 2024/03/01 08:51:25 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*gestire export var++=value
fanculo agli export concatenati*/

#include "../../include/minishell.h"

void	ft_setenv(char *name, char *value, t_env4mini *all)
{
	int		i;
	char	*temp;
	int		size;

	i = 0;
	while (all->env[i])
	{
		if (ft_strncmp(all->env[i], name, ft_strlen(name)) == 0)
		{
			free(all->env[i]);
			if (value && *value != '\0')
				all->env[i] = ft_strjoin(ft_strjoin(name, "="), value);
			else
				all->env[i] = ft_strjoin(name, "");
			return ;
		}
		i++;
	}

	if (value && *value != '\0')
		all->env[i] = ft_strjoin(ft_strjoin(name, "="), value);
	else
		all->env[i] = ft_strjoin(name, "");
	size = i + 2;
	temp = all->env[i];
	all->env = (char **)realloc(all->env, size * sizeof(char *));
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
			if (i > 0 && str[i - 1] != ' ')
				return (0);
			else
				return (-1);
		}
		i++;
	}
	return (1);
}
