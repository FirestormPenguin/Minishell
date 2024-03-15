/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/15 14:36:32 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*condition_node(t_list *list, int next_type, char **mtx, int i)
{
	list->type = next_type;
	list->mtx[0] = ft_strdup("echo");
	list->mtx[1] = ft_strdup("-n");
	list->mtx[2] = NULL;
	list->next = ft_lstnew();
	list = list->next;
	list->type = check_type(mtx[i]);
	return (list);
}

void	init_node_vars(int *j, t_list **list, t_list **h_list, int next_type)
{
	(*j) = 0;
	(*list) = ft_lstnew();
	(*list)->type = next_type;
	(*h_list) = (*list);
}

t_list	*various(t_list *list, char **mtx, int *j, int i)
{
	list->mtx[*j] = mtx[i];
	(*j)++;
	return (list);
}

t_list	*idk(t_list *list, char **mtx, int next_type, int i)
{
	if (next_type != WORD && i != 0)
		list = condition_node (list, next_type, mtx, i);
	free(mtx[i]);
	return (list);
}

t_list	*create_node(char **mtx, int *i, int *next_type)
{
	int			j;
	t_list		*list;
	t_list		*h_list;

	init_node_vars(&j, &list, &h_list, *next_type);
	while (mtx[*i])
	{
		if (check_type(mtx[*i]) != WORD)
		{
			list = idk(list, mtx, *next_type, *i);
			(*i)++;
		}
		list = various(list, mtx, &j, *i);
		(*i)++;
		if (check_type(mtx[*i]) != WORD)
		{
			*next_type = check_type(mtx[*i]);
			free(mtx[*i]);
			(*i)++;
			break ;
		}
	}
	list->mtx[j] = NULL;
	return (h_list);
}
