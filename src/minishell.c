/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/06 20:32:55 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//add built in func: deleted for fixing

void getInput(t_env4mini *all)
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
            list = parser(inputString);
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
	t_env4mini all;
	
	copy_env(envp, &all);
	//print_env_copy(&all);
	getInput(&all);

    free_env(&all);

	return 0;
}
