/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/01/17 16:40:23 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tree	*insert_pipe(t_args *tokens, int pipe_count)
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
			node = create_node("|", TOKEN_PIPE, NULL, NULL);
			rootNode = node;
			i++;
			pipe_count--;
		}
		else
		{
			node->right = create_node("|", TOKEN_PIPE, node, NULL);
			node = node->right;
			pipe_count--;
		}
	}
	return (rootNode);
}

void	bottomTopTraversTree(t_tree *traversNode)
{
	while (traversNode)
	{
		traversNode = traversNode->prev;
	}
}

t_tree  *parseTokens(t_args *tokens, t_tree *prevNode, t_tree *rootNode)
{
	t_tree *newNode;
	t_tree *tmp;

	if (tokens == NULL)
		return (NULL);
	newNode = create_node(tokens->str, tokens->type, prevNode, rootNode);
	tokens++;
	if (tokens->type == TOKEN_WORD)
		newNode->left = parseTokens(tokens, newNode, rootNode);
	else if (tokens->type != TOKEN_WORD && rootNode->right == NULL)
		rootNode->right = parseTokens(tokens, rootNode, rootNode);
	else if (tokens->type != TOKEN_WORD)
	{
		tmp = rootNode->right;
		while (rootNode->right != NULL)
		{
			tmp = tmp->right;
		}
		tmp = parseTokens(tokens, tmp->prev, rootNode);
	}
	
	return (newNode);
}

t_tree  *build_tree(t_args *tokens, int pipe_count)
{
	t_tree *rootNode;

	rootNode = NULL;
	if (pipe_count <= 0)
	{
		rootNode = create_node(tokens->str, tokens->type, NULL, NULL);
		tokens++;
	}
	else
		rootNode = insert_pipe(tokens, pipe_count);
	rootNode->parent = rootNode;
	if (tokens->type == TOKEN_WORD)
		rootNode->left = parseTokens(tokens, rootNode, rootNode);
	else if (tokens->type != TOKEN_WORD)
		rootNode->right = parseTokens(tokens, rootNode, rootNode);
	return (rootNode);
}
