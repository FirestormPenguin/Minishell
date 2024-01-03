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

t_tree *parseCommand(t_args *tokens)
{
    if (tokens == NULL || tokens->type != TOKEN_WORD)
        return NULL;

    t_tree *commandNode = create_node(tokens->str);
    tokens++;
    return (commandNode);
}

t_tree *parseOperator(t_args *tokens)
{
    if (tokens == NULL || (tokens->type != TOKEN_PIPE && tokens->type != TOKEN_REDIR &&
                           tokens->type != TOKEN_DOUBLE_OUT && tokens->type != TOKEN_HERE_DOC))
        return NULL;
    
    t_tree *operatorNode = create_node(tokens->str);
    tokens++;
    return (operatorNode);
}

t_tree *parseTokens(t_args *tokens, int *pipe_count)
{
    if (tokens == NULL)
        return (NULL);
    t_tree *leftNode = parseCommand(tokens);

    if (leftNode == NULL)
        leftNode = parseOperator(tokens);

    if (leftNode == NULL)
        return (NULL);

    tokens++;
    if (tokens->type == TOKEN_PIPE)
    {
        pipe_count++;
        tokens++;
    }

    t_tree *rightNode = parseTokens(tokens, pipe_count);

    if (rightNode != NULL)
    {
        t_tree *operatorNode = create_node("VOID");
        operatorNode->left = leftNode;
        operatorNode->right = rightNode;
        return (operatorNode);
    }
    else
    {
        return (leftNode);
    }
}

t_tree	*build_tree(t_args *args)
{
    int pipe_count = 0;
    t_tree *parsedTree = parseTokens(args, &pipe_count);
    return (parsedTree);
}
