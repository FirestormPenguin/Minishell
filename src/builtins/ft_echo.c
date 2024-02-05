#include "../include/minishell.h"

static	int	echo_parse_case(char **command_string)
{
	if (!command_string)
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
	while (command_string[++i])
	{
		printf("%s", command_string[i]);
		if (i < arg_size - 1)
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
		flag = 1
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
	if (echo_parse_case(command_string) == 2)
		return (0);
	else if (echo_parse_case(command_string) == 1)
	{
		printf("\n");
		return (0);
	}
		
	return (0);
}