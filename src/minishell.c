/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/14 15:11:40 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int last_exit_code;

void getInput(t_env4mini *all, t_parser *pars)
{
	char *inputString;
	t_list *list;

	while (1)
	{
		inputString = readline("Minishell: ");
		if (!inputString)
			break;
		else
		{
			list = parser(inputString, pars);
			add_history(inputString);
			exe(list, all);
		}
		free(inputString);
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	last_exit_code = 0;
	t_env4mini *all = ft_calloc(1, sizeof(t_env4mini));
	t_parser pars;

	copy_env(envp, all);
	pars.cp_env = all;
	//print_env_copy(pars.cp_env);
	getInput(all, &pars);

	free_env(all);
	free(all);

	return 0;
}
