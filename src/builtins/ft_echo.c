/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:36:06 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/06 15:36:06 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	echo_parse_case(char **command_string)
{
	//printf("%s\n", command_string[1]);
	if (!command_string[1])
		return (1);
	else if (!command_string[2] && !ft_strcmp(command_string[1], "-n"))
		return (2); 
	return (0);
}

static	void print_arg(char **command_string, int index, int flag, int arg_size)
{
	if (flag == 1)
		index++;
	while (command_string[arg_size])
		arg_size++;
	while (command_string[++index])
	{
		printf("%s", command_string[index]);
		if (index < arg_size - 1)
			printf(" ");
	}
		
	if (flag == 0)
		printf("\n");
}

static	int	flag_check(char **command_string, int flag)
{
	int	n_number;

	n_number = 1;

	if (command_string[1][0] == '-' && command_string[1][1] == 'n')
	{
		flag = 1;
		while (command_string[1][++n_number])
		{
			if (command_string[1][n_number] == '\0' 
				&& command_string[1][n_number] != 'n')
				flag = 0;
		}
	}
	return (flag);
}

int	ft_echo(char **command_string)
{
	int flag;
	int i;
	int arg_size;

	arg_size = 0;
	flag = 0;
	i = 0;
	if (echo_parse_case(command_string) == 2)
		return (0);
	else if (echo_parse_case(command_string) == 1)
	{
		printf("\n");
		return (0);
	}
	flag = flag_check(command_string, flag);
	print_arg(command_string, i, flag, arg_size);
	return (0);
}