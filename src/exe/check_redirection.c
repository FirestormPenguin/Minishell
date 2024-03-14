/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/03/14 23:39:57 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_pipe_at_first(t_list *list, int flag)
{
	if (list->type == PIPE && flag == 0)
	{
		printf("parse error near '|'\n");
		return (1);
	}
	return (0);
}

void	parse_error_gen(t_list *list)
{
	char	*s;

	s = malloc(sizeof(char) * 5);
	if (list->next)
	{
		if (list->next->type == IN)
			s = "<";
		else if (list->next->type == OUT)
			s = ">";
		else if (list->next->type == DOUBLE_OUT)
			s = ">>";
		else if (list->next->type == HERE_DOC)
			s = "<<";
		else if (list->next->type == PIPE)
			s = "|";
	}
	printf("parse error near '%s'\n", s);
	free (s);
}

int	check_mtx_null(t_list *list)
{
	if (list->type != WORD && !list->next && !list->mtx)
	{
		printf("parse error near ''\n");
		return (1);
	}
	else if (ft_strcmp(list->mtx[0], "\n") == 0
		|| ft_strcmp(list->mtx[0], " ") == 0
		|| ft_strcmp(list->mtx[0], "") == 0)
	{
		printf("parse error near ' '\n");
		return (1);
	}
	return (0);
}

int check_double_red_pipe(t_list *list)
{
	if (list->type != WORD && !list->mtx && (!list->next || list->next->type != WORD))
	{
		printf("parse error near ''\n");
		return (1);
	}
	else if (list->type != WORD && (check_type(list->mtx[0])) != WORD)
	{
		printf("parse error near '%s'\n", list->mtx[0]);
		return (1);
	}
	return (0);
}

int	check_error_redirection(t_list *list)
{
	int		flag;

	flag = 0;
	while (list)
	{
		if (check_pipe_at_first(list, flag) == 1)
			return (1);
		flag = 1;
		if (list->type == PIPE && list->next->type != WORD && list->next->mtx[0])
		{
			list = list->next;
			continue ;
		}
		else if (check_double_red_pipe(list) == 1)
		{
			return (1);
		}
		else if (check_mtx_null(list) == 1)
			return (1);
		list = list->next;
	}
	return (0);
}
