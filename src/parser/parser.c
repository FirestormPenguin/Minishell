/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/01/26 17:35:50 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// t_args	*fill_struct(char **mtx, int count)
// {
// 	t_args	*tmp;
// 	int		i;

// 	i = -1;
// 	tmp = malloc((count) * sizeof(t_args));
// 	while (mtx[++i])
// 	{
// 		tmp[i].str = mtx[i];
// 		tmp[i].type = TOKEN_EMPTY;
// 	}
// 	return (tmp);
// }

// void check_type(t_args *args, int count)
// {
// 	int i;

// 	i = -1;
// 	while (++i < count)
// 	{
// 		if (ft_strcmp(args[i].str, "|") == 0)
// 			args[i].type = TOKEN_PIPE;
// 		else if (ft_strcmp(args[i].str, "<") == 0 || ft_strcmp(args[i].str, ">") == 0)
// 			args[i].type = TOKEN_REDIR;
// 		else if (ft_strcmp(args[i].str, ">>") == 0)
// 			args[i].type = TOKEN_DOUBLE_OUT;
// 		else if (ft_strcmp(args[i].str, "<<") == 0)
// 			args[i].type = TOKEN_HERE_DOC;
// 		else
// 			args[i].type = TOKEN_WORD;
// 	}
// }

int check_type(char *str)
{
	int type;

	type = 0;
	if (ft_strcmp(str, "|") == 0)
		type = PIPE;
	else if (ft_strcmp(str, "<") == 0)
		type = IN;
	else if (ft_strcmp(str, ">") == 0)
		type = OUT;
	else if (ft_strcmp(str, ">>") == 0)
		type = DOUBLE_OUT;
	else if (ft_strcmp(str, "<<") == 0)
		type = HERE_DOC;
	else
		type = WORD;
	return (type);
}

static t_list	*ft_lstnew(char ***mtx)
{
	t_list	*tmp_node;
	char	**tmp_mtx;
	int		i;

	i = 0;
	tmp_node = NULL;
	tmp_node = malloc(sizeof(t_list));
	tmp_node->type = NULL;
	// tmp_node->type = check_type((char *)*mtx - 1);
	tmp_node->next = NULL;
	while (*mtx)
	{
		printf ("\t");
		tmp_node->mtx[i] = *mtx;
		i++;
		*mtx++;
		if (check_type((char *)*mtx) != 0)
		{
			*mtx++;
			break;
		}
	}
	tmp_mtx = malloc(sizeof(char *) * i);
	tmp_node->mtx = tmp_mtx;
	return (tmp_node);
}

t_list	*init_list(char **mtx)
{
	int		i;
	t_list	**list_h;
	t_list	*list;
	int		tmp_type;

	i = 0;
	list_h = NULL;
	list = NULL;
	tmp_type = WORD;
	while (mtx)
	{
		if (i == 0)
		{
			list = ft_lstnew(&mtx);
			*list_h = list;
		}
		else
		{
			list->next = ft_lstnew(&mtx);
			list = list->next;
		}
		i++;
	}
	return (*list_h);
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

void	scroll_mtx(char ***mtx)
{
	int i = 0;
	while (*mtx != NULL)
	{
		printf("\tmtx: %s\n", **mtx);
		mtx++;
	}
}

void	tokenize_string(char *str)
{
	// t_args	*tokens;
	t_list	**parent_node;
	char	**mtx;
	int		arg_count;

	mtx = tokenizer(str, &arg_count);
	if (mtx == NULL)
		return ;
	scroll_mtx(&mtx);
	//parent_node = init_list(mtx);
	// tokens = fill_struct(mtx, arg_count);
	// check_type(tokens, arg_count);
	// scroll_list(parent_node);
}
