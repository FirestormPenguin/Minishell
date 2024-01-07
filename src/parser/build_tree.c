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

t_tree *parseTokens(t_args *tokens, t_tree *prevNode)
{
    t_tree *rootNode;
    t_tree *leftNode;
    t_tree *rightNode;

    if (tokens == NULL)
        return (NULL);
    rootNode = create_node(tokens->str);
    rootNode->prev = prevNode;
    tokens++;
    rootNode->left = leftNode;
    rootNode->right = rightNode;

    /*in questo if devo inserire uno scorrimento che ogni volta che
    vuole inserire un nuovo token deve prima tornare ai nodi precedenti
    e controllare se c'e' dello spazio libero, ergo, se il token e'
    una parola vanno inseriti a sinsitra, mentre se e' un divisore
    va a destra
    Oppure una nuova funzione che sara' quella effettivamente ricorsiva*/
    if (tokens->type == TOKEN_WORD)
        leftNode = parseTokens(tokens, rootNode);
    else
        rightNode = parseTokens(tokens, rootNode);
    return (rootNode);
}

t_tree	*build_tree(t_args *tokens)
{
    t_tree *rootNode;
    t_tree *leftNode;
    t_tree *rightNode;

    rootNode = create_node("VOID");
    rootNode->left = leftNode;
    rootNode->right = rightNode;
    rootNode->prev = NULL;
    leftNode = parseTokens(tokens, rootNode);
    rightNode = parseTokens(tokens, rootNode);
    

    parseTokens(args, rootNode);
    return (rootNode);
}
