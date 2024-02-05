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

static t_list	*ft_lstnew()
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

t_list	*init_list(char **mtx)
{
	int		i;
	int		j;
	t_list	*list_h;
	t_list	*list;
	int		next_type;

	i = 0;
	list_h = NULL;
	list = NULL;
	next_type = WORD;
	while (mtx[i])
	{
		if (i == 0)
		{
			if (check_type(mtx[i]) != WORD)
			{
				next_type = check_type(mtx[i]);
				i++;
			}
			j = 0;
			list = ft_lstnew();
			list->type = next_type;
			while (mtx[i])
			{
				list->mtx[j] = mtx[i];
				j++;
				i++;
				if (check_type(mtx[i]) != WORD)
				{
					next_type = check_type(mtx[i]);
					i++;
					break;
				}
			}
			list_h = list;
		}
		else
		{
			j = 0;
			list->next = ft_lstnew();
			list->next->type = next_type;
			while (mtx[i])
			{
				list->next->mtx[j] = mtx[i];
				j++;
				i++;
				if (check_type(mtx[i]) != WORD)
				{
					next_type = check_type(mtx[i]);
					i++;
					break;
				}
			}
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
