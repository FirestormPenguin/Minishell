/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/15 14:23:07 by egiubell         ###   ########.fr       */
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

int	check_type(char *str)
{
	int	type;

	type = 0;
	if (!str)
		return (WORD);
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

void	scroll_list(t_list *node)
{
	int	i;

	while (node)
	{
		i = -1;
		printf ("nodo nuovo\n");
		printf("\ttype : %d\n", node->type);
		while (node->mtx[++i])
		{
			if (node->mtx[i] == NULL)
				break ;
			printf("\t%s\n", node->mtx[i]);
		}
		node = node->next;
	}
}
