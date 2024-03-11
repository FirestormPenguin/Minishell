/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/03/09 15:20:51 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_grb_collector	*set_garbage_collector(t_list *list, t_process *proc)
{
	t_grb_collector	*tmp;

	//printf("\tpre proc: %p\n", proc);
	tmp = malloc(sizeof(t_grb_collector));
	tmp->list_ptr = list;
	tmp->env_ptr = proc->all;
	tmp->parser_ptr = proc->all->pars;
	tmp->proc_ptr = proc;
	//printf("\tpre proc P: %p\n", tmp->proc_ptr);
	return (tmp);
}

void	free_double_pointer(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
	return ;
}

void	init_vars(t_process *proc, int *i)
{
	//proc->path = ft_calloc(1000, sizeof(char));
	proc->args = ft_calloc(1000, sizeof(char *));
	*i = 0;
}

void	set_last_args(t_process *proc, int j)
{
	if (proc->args)
	{
		if (!proc->args[j] && !proc->args[j - 1])
			proc->args = NULL;
		else if (proc->args[j - 1] && proc->args[j - 1][0] == '\0')
			proc->args[j - 1] = NULL;
		else
			proc->args[j] = NULL;
	}
	else
		proc->args = NULL;
}

t_list	*fill_args(t_list *list, t_process *proc, int i)
{
	int		j;

	j = 0;
	while (list)
	{
		i = 0;
		//printf("type: %d %d %d\n", list->type, i, j);
		if (list->type != WORD && list->type != PIPE)
		//{
			i++;
			//j++;
		//}
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
