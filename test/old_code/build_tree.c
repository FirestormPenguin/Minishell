/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/01/26 18:16:00 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_args	*fill_struct(char **mtx, int count)
{
	t_args	*tmp;
	int		i;

	i = -1;
	tmp = malloc((count) * sizeof(t_args));
	while (mtx[++i])
	{
		tmp[i].str = mtx[i];
		tmp[i].type = TOKEN_EMPTY;
	}
	return (tmp);
}

void check_type(t_args *args, int count)
{
	int i;

	i = -1;
	while (++i < count)
	{
		if (ft_strcmp(args[i].str, "|") == 0)
			args[i].type = TOKEN_PIPE;
		else if (ft_strcmp(args[i].str, "<") == 0 || ft_strcmp(args[i].str, ">") == 0)
			args[i].type = TOKEN_REDIR;
		else if (ft_strcmp(args[i].str, ">>") == 0)
			args[i].type = TOKEN_DOUBLE_OUT;
		else if (ft_strcmp(args[i].str, "<<") == 0)
			args[i].type = TOKEN_HERE_DOC;
		else
			args[i].type = TOKEN_WORD;
	}
}

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

void assignNotWord(t_tree *newNode, t_tree *rootNode, int deleted_pipe)
{
	if (rootNode && rootNode->type != TOKEN_PIPE)
	{
		if (rootNode->right)
			assignNotWord(newNode, rootNode->right, deleted_pipe);
		else
			rootNode->right = newNode;
	}
	else if (rootNode && rootNode->type == TOKEN_PIPE && deleted_pipe == 0 )
	{
		if (rootNode->left)
			assignNotWord(newNode, rootNode->right, deleted_pipe);
		else
			rootNode->right = newNode;
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
		assignNotWord(newNode, rootNode, deleted_pipe);
	tokens++;
	token_count--;
	if (tokens->type == TOKEN_PIPE && deleted_pipe == 0)
	{
		tokens++;
		token_count--;
		deleted_pipe = 1;
	}
	if (tokens->type == TOKEN_WORD)
		newNode->left = parseTokens(tokens, newNode, rootNode, token_count, deleted_pipe);
	else
	{
		if (rootNode->type == TOKEN_PIPE && deleted_pipe == 0)
			tmp = rootNode->left;
		else
			tmp = rootNode;
		while (tmp->right != NULL)
		{
			tmp = tmp->right;
		}
		tmp->right = parseTokens(tokens, tmp, rootNode, token_count, deleted_pipe);
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
