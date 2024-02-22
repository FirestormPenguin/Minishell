/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/22 11:29:31 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int last_exit_code;

void	sigint_handle(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();

}

void	sigquit_handle(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void getInput(t_env4mini *all, t_parser *pars)
{
	char *inputString;
	t_list *list;

	while (1)
	{
		signal(SIGINT, sigint_handle);
		signal(SIGQUIT, SIG_IGN);
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
