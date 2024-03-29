/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:54:38 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/06 15:54:38 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(char **args, t_grb_collector *grb_ptr)
{
	int	exit_value;

	exit_value = 0;
	write(1, "exit\n", 5);
	if (args[1])
	{
		if (ft_isstrdigit(args[1]))
		{
			exit_value = ft_atoi(args[1]) % 256;
			if (args[2])
			{
				printf("arg 1; %s\n", args[1]);
				printf("minishell: exit: too many arguments\n");
			}
		}
		else
		{
			printf("arg 1; %s\n", args[1]);
			printf("minishell: exit: numeric argument required\n");
			exit_value = 2;
		}
	}
	free_exit(exit_value, grb_ptr);
}
