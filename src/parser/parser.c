/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/09 10:45:14 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_lstnew(void)
{
	t_list	*tmp_node;

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
	t_list		*h_list;

	j = 0;
	list = ft_lstnew();
	list->type = *next_type;
	h_list = list;
	while (mtx[*i])
	{	
		//printf("+|%s| %d %d\n", mtx[*i], *i, *next_type);
		if (check_type(mtx[*i]) != WORD)
		{
			if (*next_type != WORD && *i != 0)
			{
				//printf("i: %d nt: %d t: %d\n", *i, *next_type, check_type(mtx[*i]));
				list->type = *next_type;
				list->mtx[0] = ft_strdup("echo");
				list->mtx[1] = ft_strdup("-n");
				list->mtx[2] = NULL;
				list->next = ft_lstnew();
				list = list->next;
				list->type = check_type(mtx[*i]);
			}
			(*i)++;
		}
		//printf("++|%s| %d %d\n", mtx[*i], *i, *next_type);
		/*if (check_type(mtx[*i]) != WORD)
		{
			*next_type = check_type(mtx[*i]);
			free(mtx[*i]);
			(*i)++;
			break ;
		}*/
		list->mtx[j] = mtx[*i];
		j++;
		(*i)++;
		if (check_type(mtx[*i]) != WORD)
		{
			//if (j == 0)
			//	list->mtx[j++] = ft_strdup("");
			*next_type = check_type(mtx[*i]);
			free(mtx[*i]);
			(*i)++;
			break ;
		}
		//printf("+|%s| %d\n", mtx[*i], *i);
	}
	list->mtx[j] = NULL;
	return (h_list);
}

void	init_first_node(t_list **list, char **mtx, int *i, int *next_type)
{
	if (check_type(mtx[*i]) != WORD)
		*next_type = check_type(mtx[*i]);
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
			//printf("f-%s %d\n", list->mtx[0], list->type);
		}
		else
		{
			while (list->next)
				list = list->next;
			list->next = create_node(mtx, &i, &next_type);
			while (list->next)
			//{
				//printf("-> .%s.%d\n", list->next->mtx[0], list->next->type);
				list = list->next;
			//}
			//printf("f+%s %d\n", list->mtx[0], list->type);
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
