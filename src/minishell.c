/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/05 15:42:03 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void getInput(t_env4mini *all)
{
    char *inputString;
    t_list *list;

    while (1) 
    {
        inputString = readline("Minishell: ");
        if (!inputString)
            break;
        if (!ft_strcmp(inputString, "exit")) 
        {
            free(inputString);
            break;
        } 
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

	//fix: Creare funzione separata
	int i = 0;
	while (all.env[i] != NULL)
	{
		free(all.env[i]);
		i++;
	}
	free(all.env);

	return 0;
}

