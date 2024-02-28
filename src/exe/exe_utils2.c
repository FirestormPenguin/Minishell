/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/26 11:19:50 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_double_pointer(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
	return ;
}

void	init_vars(t_process *proc, int *i, t_env4mini *all)
{
	char	*tmp_args;

	tmp_args = NULL;
	proc->path = ft_calloc(1000, sizeof(char));
	proc->args = ft_calloc(1000, sizeof(char *));
	*i = 0;
}

void	set_last_args(t_process *proc, int j)
{
	if (proc->args[j - 1][0] == '\0')
		proc->args[j - 1] = NULL;
	else
		proc->args[j] = NULL;
}

t_list	*fill_args(t_list *list, t_process *proc, int i)
{
	int	j;

	j = 0;
	while (list)
	{
		i = 0;
		if (list->type != WORD && list->type != PIPE)
			i++;
		while (list->mtx[i])
		{
			proc->args[j] = malloc(strlen(list->mtx[i]) + 1);
			if (!proc->args[j])
			{
				perror("malloc failed");
				exit(EXIT_FAILURE);
			}
			strcpy(proc->args[j++], list->mtx[i++]);
		}
		list = list->next;
		if (list == NULL || list->type == PIPE)
			break ;
	}
	set_last_args(proc, j);
	return (list);
}
