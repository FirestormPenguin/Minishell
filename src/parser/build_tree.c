/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/01/19 16:27:30 by egiubell         ###   ########.fr       */
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

void assignTmp(t_tree *tmp, t_tree *rootNode)
{
	if (rootNode)
	{
		if (rootNode->right != NULL)
			assignTmp(tmp, rootNode->right);
		else
			rootNode->right = tmp;
	}
}

t_tree  *parseTokens(t_args *tokens, t_tree *prevNode, t_tree *rootNode, int token_count, int deleted_pipe)
{
	t_tree *newNode;
	t_tree *tmp;

	if (token_count <= 0)
		return (NULL);
	newNode = create_node(tokens->str, tokens->type, prevNode, rootNode);
	if (newNode->type != TOKEN_WORD)
		assignTmp(newNode, rootNode);
	tokens++;
	token_count--;
	// if (tokens->type == TOKEN_PIPE && deleted_pipe == 0)
	// {
	// 	/*questa parte funziona ma bisogna far si che non solo salti la pipe ma anche
	// 	che faccia tornare l'esecuzione come fosse un normale token non word*/
	// 	tokens++;
	// 	token_count--;
	// 	deleted_pipe = 1;
	// }
	if (tokens->type == TOKEN_WORD)
		newNode->left = parseTokens(tokens, newNode, rootNode, token_count, deleted_pipe);
	else
	{
		tmp = rootNode;
		while (tmp->right != NULL)
		{
			tmp = tmp->right;
		}
		tmp->right = parseTokens(tokens, tmp, rootNode, token_count, deleted_pipe);
		// assignTmp(tmp, rootNode);
	}
	return (newNode);
}

t_tree  *build_tree(t_args *tokens, int pipe_count, int token_count)
{
	t_tree *rootNode;
	int		deleted_pipe;

	rootNode = NULL;
	deleted_pipe = 0;
	if (pipe_count <= 0)
	{
		rootNode = create_node(tokens->str, tokens->type, NULL, NULL);
		tokens++;
		token_count--;
	}
	else
		rootNode = insert_pipe(tokens, pipe_count);
	rootNode->parent = rootNode;
	if (tokens->type == TOKEN_WORD)
		rootNode->left = parseTokens(tokens, rootNode, rootNode, token_count, deleted_pipe);
	else
		rootNode->right = parseTokens(tokens, rootNode, rootNode, token_count, deleted_pipe);
	return (rootNode);
}
