/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/26 11:15:06 by mivendit         ###   ########.fr       */
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
	int			j;
	t_list		*list;

	j = 0;
	list = ft_lstnew();
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
			break ;
		}
	}
	list->mtx[j] = NULL;
	return (list);
}

void	init_first_node(t_list **list, char **mtx, int *i, int *next_type)
{
	if (check_type(mtx[*i]) != WORD)
	{
		*next_type = check_type(mtx[*i]);
		(*i)++;
	}
	*list = create_node(mtx, i, next_type);
}

t_list	*init_list(char **mtx)
{
	int		i;
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
			init_first_node(&list, mtx, &i, &next_type);
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

t_list	*parser(char *str, t_parser *pars)
{
	t_list	*list_head;
	char	**mtx;
	int		arg_count;

	mtx = tokenizer(str, &arg_count, pars);
	if (mtx == NULL)
		return (NULL);
	list_head = init_list(mtx);
	//free_double_pointer(mtx);
	return (list_head);
}
