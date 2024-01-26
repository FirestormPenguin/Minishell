/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/01/26 18:15:45 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static t_list	*ft_lstnew()
{
	t_list	*tmp_node;
	int		i;

	i = 0;
	tmp_node = NULL;
	tmp_node = malloc(sizeof(t_list));
	tmp_node->mtx = malloc (sizeof(char *) * 50);
	tmp_node->type = 0;
	tmp_node->next = NULL;
	return (tmp_node);
}

t_list	*init_list(char **mtx)
{
	int		i;
	int		j;
	t_list	*list_h;
	t_list	*list;
	int		tmp_type;

	i = 0;
	list_h = NULL;
	list = NULL;
	tmp_type = WORD;
	while (mtx[i])
	{
		if (i == 0)
		{
			j = 0;
			list = ft_lstnew();
			while (mtx[i])
			{
				list->mtx[j] = mtx[i];
				j++;
				i++;
				if (check_type(mtx[i]) != 0)
					break;
			}
			list_h = list;
		}
		else
		{
			j = 0;
			list->next = ft_lstnew();
			while (mtx[i])
			{
				list->mtx[j] = *mtx[i];
				j++;
				i++;
				if (check_type(mtx[i]) != 0)
					break;
			}
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
		//printf ("nodo numero: %d\n", i);
		while (node->mtx[++i])
			printf("\t%s\n", node->mtx[i]);
		node = node->next;
	}
}

void	tokenize_string(char *str)
{
	t_list	**parent_node;
	char	**mtx;
	int		arg_count;

	mtx = tokenizer(str, &arg_count);
	if (mtx == NULL)
		return ;
	parent_node = init_list(mtx);
	scroll_list(parent_node);
}
