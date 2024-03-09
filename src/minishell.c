/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/09 14:57:58 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_last_exit_code;

void	get_input(t_env4mini *all, t_parser *pars)
{
	char	*input_string;
	t_list	*list;

	all->pars = pars;
	while (1)
	{
		signal(SIGINT, sigint_handle);
		signal(SIGQUIT, SIG_IGN);
		input_string = readline("Minishell: ");
		if (!input_string)
			break ;
		else
		{
			list = parser(input_string, pars);
			add_history(input_string);
			exe(list, all);
			//free_list(list);
		}
		free(input_string);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env4mini	*all;
	t_parser	pars;

	(void)ac;
	(void)av;
	g_last_exit_code = 0;
	all = ft_calloc(1, sizeof(t_env4mini));
	copy_env(envp, all);
	ft_setenv("SHELL", "/minishell", all);
	increment_shlvl(all);
	pars.cp_env = all;
	get_input(all, &pars);
	free_env(all);
	free(all);
	return (0);
}
