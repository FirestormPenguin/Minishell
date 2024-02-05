/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/05 13:31:41 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	t_list	*ft_lstnew(void)
{
	t_list	*tmp_node;
	int		i;

	i = 0;
	tmp_node = NULL;
	tmp_node = malloc(sizeof(t_list));
	tmp_node->mtx = malloc (sizeof(char *) * 100);
	tmp_node->type = 0;
	tmp_node->next = NULL;
	return (tmp_node);
}

static	t_list	*create_node(char **mtx, int *i, int *next_type)
{
	int j = 0;
	t_list *list = ft_lstnew();
	list->type = *next_type;

	while (mtx[*i])
	{
		list->mtx[j] = mtx[*i];
		j++;
		(*i)++;
		if (check_type(mtx[*i]) != WORD)
		{
			*next_type = check_type(mtx[*i]);
			(*i)++;
			break;
		}
	}
	return list;
}

t_list	*init_list(char **mtx)
{
	int i = 0;
	t_list *list_h = NULL;
	t_list *list = NULL;
	int next_type = WORD;

	while (mtx[i])
	{
		if (i == 0)
		{
			if (check_type(mtx[i]) != WORD)
			{
				next_type = check_type(mtx[i]);
				i++;
			}
			list = create_node(mtx, &i, &next_type);
			list_h = list;
		}
		else
		{
			list->next = create_node(mtx, &i, &next_type);
			list = list->next;
		}
	}
	return (list_h);
}

t_list	*parser(char *str)
{
	t_list	*list_head;
	char	**mtx;
	int		arg_count;

	mtx = tokenizer(str, &arg_count);
	if (mtx == NULL)
		return (NULL);
	list_head = init_list(mtx);
	return (list_head);
}
