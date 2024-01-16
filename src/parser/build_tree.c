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

t_tree  *insert_pipe(t_args *tokens, int pipe_count)
{
    t_tree *rootNode;
    t_tree *node;
    int i;

    rootNode = NULL;
	node = NULL;
    i = 0;
    while (pipe_count > 0)
    {
        if (i == 0)
        {
            node = create_node("|", TOKEN_PIPE, NULL);
            rootNode = node;
            i++;
            pipe_count--;
        }
        else
        {    
            node->right = create_node("|", TOKEN_PIPE, node);
            node = node->right;
            pipe_count--;
        }
    }
    return (rootNode);
}

void    bottomTopTraversTree(t_tree *traversNode)
{
    while (traversNode)
    {
        traversNode = traversNode->prev;
        if (traversNode->type == TOKEN_WORD);
    }
}

t_tree  *parseTokens(t_args *tokens, t_tree *prevNode)
{
    t_tree *newNode;

    if (tokens == NULL)
        return (NULL);
    newNode = create_node(tokens->str, tokens->type, prevNode);
    tokens++;
    if (newNode->left == NULL)
        newNode->left = parseTokens(tokens, newNode);
    else
        newNode->right = parseTokens(tokens, newNode);
    return (newNode);
}

t_tree  *build_tree(t_args *tokens, int pipe_count)
{
    t_tree *rootNode;
    
    rootNode = NULL;
    if (pipe_count <= 0)
    {
        rootNode = create_node(tokens->str, tokens->type, NULL);
        tokens++;
    }
    else
        rootNode = insert_pipe(tokens, pipe_count);
    rootNode->left = parseTokens(tokens, rootNode);
    return (rootNode);
}
