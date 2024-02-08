/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 00:33:36 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/08 00:33:36 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_env_value(char *key, t_env4mini *all)
{
    int i = 0;
    int key_len = ft_strlen(key);

    while (all->env[i] != NULL)
    {
        // Check if the key is a prefix of the environment variable string
        if (ft_strncmp(all->env[i], key, key_len) == 0 && all->env[i][key_len] == '=')
        {
            // Return a pointer to the value part of the string
            return all->env[i] + key_len + 1;
        }
        i++;
    }

    // Return NULL if the key was not found
    return NULL;
}

int	ft_cd(char **args, t_env4mini *all)
{
    char *home = get_env_value("HOME", all);

    printf("args[0]: %s\n", args[0]);

    if (args[1] != NULL && !ft_strcmp(args[1], "$HOME"))
    {
        printf("args[1]: %s\n", args[1]);
        home = get_env_value("HOME", all);
        if (home == NULL || chdir(home) == -1)
        {
            perror("cd");
            return (1);
        }
    }
    else if (!args[1])
    {
        home = get_env_value("HOME", all);
        printf("home: %s\n", home);
        if (home == NULL || chdir(home) == -1)
        {
            args[1] = home;
            perror("cd");
            return (1);
        }
    }
    else
    {
        printf("args[1]: %s\n", args[1]);
        printf("home: %s\n", home);
        if (chdir(args[1]) == -1)
        {
            printf("minishell: cd: %s: No such file or directory\n", args[1]);
            return (1);
        }
    }
    return (0);
}