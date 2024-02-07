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

/* void ft_exit(char **args)
{
    int exit_value = 0;
    printf("exit\n");

    if (args[1])
    {
        if (ft_isstrnum(args[1]))
        {
            exit_value = atoi(*args) % 256;
            if (args[2])
            {
                perror("minishell: exit: ");
                return;
            }
        }
        else
        {
            perror("minishell: exit: ");
            exit_value = 2;
        }
    }

    free_exit(exit_value);
} */