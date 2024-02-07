/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/06 23:32:33 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_error_redirection(t_list *list)
{
	while (list)
	{
		if (list->type != WORD && check_type(list->mtx[0]) != WORD)
		{
			printf("parse error near '%s'\n", list->mtx[0]);
			return (1);
		}
		else if (ft_strcmp(list->mtx[0], "\n") == 0 || ft_strcmp(list->mtx[0], " ") == 0 || ft_strcmp(list->mtx[0], "") == 0)
		{
			printf("parse error near '%s'\n", list->mtx[0]);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int setup_redirection(t_list *list)
{
	while (list)
	{
		if (list->type != WORD && list->type != PIPE)
			redirections(list);
		else if (list->type == PIPE)
			return (0);
		list = list->next;
	}
	return (0);
}

void	init_vars(char **path, char ***args, int *i)
{
	*path = malloc (sizeof(char) * 50);
	*args = malloc (sizeof(char *) * 50);
	*i = 0;
	strcpy(*path, "/bin/");
}

char	**fill_args(t_list *list, char **args, int i)
{
	int j;
	
	j = 0;
	while (list->mtx[i])
		{
			args[j] = malloc (sizeof(char) * 50);
			strcpy(args[j], list->mtx[i]);
			i++;
			j++;
		}
	args[j] = NULL;
	return (args);
}

int	check_mtx(t_list *list, char *path, char **args, int i)
{
	if (!list->mtx[i])
	{
		free_all_generic(path, args);
		return (1);
	}
	return (0);
}

