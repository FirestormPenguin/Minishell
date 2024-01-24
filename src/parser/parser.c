/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/01/24 18:47:33 by egiubell         ###   ########.fr       */
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

static t_list	*ft_lstnew(int *i, t_args *tokens, int type)
{
	t_list	*tmp_node;
	char	**tmp_mtx;
	int j;

	j = 0;
	tmp_node = NULL;
	tmp_node = malloc(sizeof(t_list));
	tmp_node->type = type;
	tmp_node->next = NULL;

	while (j)
	{
		tmp_mtx[j] = tokens[*i].str;
		*i++;
		j++;
		if (tokens[*i].type != TOKEN_WORD || tokens[*i].str == NULL)
		{
			*i++;
			break;
		}
	}
	tmp_mtx = malloc(sizeof(char *) * j);
	tmp_node->mtx = tmp_mtx;
	return (tmp_node);
}

t_list	*init_list(t_args *tokens, int tokens_count)
{
	int		i;
	t_list	*list_h;
	t_list	*list;
	int		tmp_type;

	i = -1;
	list_h = NULL;
	list = NULL;
	tmp_type = WORD;
	while (++i <= tokens_count)
	{
		if (tokens->type != TOKEN_WORD)
			tmp_type = tokens->type;
		if (i == 0)
		{
			list = ft_lstnew(&i, tokens, tmp_type);
			list_h = list;
		}
		else
		{
			list->next = ft_lstnew(&i, tokens, tmp_type);
			list = list->next;
		}
	}
	return (list_h);
}

void scroll_list(t_list *node)
{
	int i;

	while (node)
	{
		i = -1;
		while (node->mtx[++i])
			printf("mtx %s\n", node->mtx[i]);
		printf("\n");
		node = node->next;
	}
}

void	tokenize_string(char *str)
{
	t_args	*tokens;
	t_list	*parent_node;
	char	**mtx;
	int		arg_count;

	mtx = tokenizer(str, &arg_count);
	if (mtx == NULL)
		return ;
	tokens = fill_struct(mtx, arg_count);
	check_type(tokens, arg_count);
	parent_node = init_list(tokens, arg_count);
	scroll_list(parent_node);
}
