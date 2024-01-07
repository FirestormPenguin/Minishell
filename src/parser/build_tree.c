/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirko <mirko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/12/12 17:01:22 by mirko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tree *parseTokens(t_args *tokens)
{
    t_tree *rootNode;
    t_tree *leftNode;
    t_tree *rightNode;
    if (tokens == NULL)
        return (NULL);
    rootNode = create_node(tokens->str);
    tokens++;
    if (tokens->type == TOKEN_WORD)
    {
        rightNode = NULL;
        leftNode = parseTokens(tokens);
    }
    else
    {
        leftNode = NULL;
        rightNode = parseTokens(tokens);
    }
    rootNode->left = leftNode;
    rootNode->right = rightNode;
        return (rootNode);
}

t_tree	*build_tree(t_args *args)
{
    t_tree *parsedTree = parseTokens(args);
    return (parsedTree);
}
