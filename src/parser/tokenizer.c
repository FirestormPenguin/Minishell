/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spiacent <spiacent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/12/07 16:46:11 by spiacent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **tokenizer(char *input, int *token_count)
{
    char    *input_copy;
    char    *div;
    int     count;
    char    *token;
    char    **tokens;
    int     i;

	div = "| ";
    count = 0;
    i = 0;
    input_copy = ft_strdup(input);
    token = ft_strtok(input_copy, div);
    while (token != NULL)
    {
        count++;
        token = ft_strtok(NULL, div);
    }
    tokens = malloc((count + 1) * sizeof(char **));
    token = ft_strtok(input, div);
    while (token != NULL)
    {
        tokens[i] = ft_strdup(token);
        if (tokens[i] == NULL)
            exit(1);
        i++;
        token = ft_strtok(NULL, div);
    }
    tokens[i] = NULL;
    *token_count = count;
    free(input_copy);
    return (tokens);
}

/*gestire "" nel tokenizer
fare lexer che controlla che il lessico sia corretto
fare come matrice di una struct con value e tipologia*/