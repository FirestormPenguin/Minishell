/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:17:30 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/20 02:18:19 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(char **args, t_env4mini *all)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (all->env[j])
		{
			if (ft_strncmp(all->env[j], args[i], ft_strlen(args[i])) == 0)
			{
				free(all->env[j]);
				while (all->env[j])
				{
					all->env[j] = all->env[j + 1];
					j++;
				}
				break ;
			}
			j++;
		}
		i++;
	}
}
