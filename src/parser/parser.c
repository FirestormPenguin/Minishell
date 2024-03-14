/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/15 00:51:05 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_first_node(t_list **list, char **mtx, int *i, int *next_type)
{
	if (check_type(mtx[*i]) != WORD)
		*next_type = check_type(mtx[*i]);
	*list = create_node(mtx, i, next_type);
}

void	init_list_vars(int *i, t_list **list_h, t_list **list, int *next_type)
{
	*i = 0;
	*list_h = NULL;
	*list = NULL;
	*next_type = WORD;
}

t_list	*init_list(char **mtx)
{
	int		i;
	t_list	*list_h;
	t_list	*list;
	int		next_type;

	init_list_vars(&i, &list_h, &list, &next_type);
	while (mtx[i])
	{
		if (i == 0)
		{
			init_first_node(&list, mtx, &i, &next_type);
			list_h = list;
		}
		else
		{
			while (list->next)
				list = list->next;
			list->next = create_node(mtx, &i, &next_type);
			while (list->next)
				list = list->next;
		}
	}
	free(mtx);
	mtx = NULL;
	return (list_h);
}

t_list	*parser(char *str, t_parser *pars)
{
	t_list	*list_head;
	char	**mtx;
	int		arg_count;

	mtx = tokenizer(str, &arg_count, pars);
	if (mtx == NULL)
		return (NULL);
	list_head = init_list(mtx);
	return (list_head);
}
