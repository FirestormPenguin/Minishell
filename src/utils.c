/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:27:21 by egiubell          #+#    #+#             */
/*   Updated: 2024/03/14 21:40:56 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_list(t_list *list)
{
	int		i;
	t_list	*tmp;

	while (list)
	{
		i = 0;
		while (list->mtx[i])
		{
			free(list->mtx[i]);
			list->mtx[i] = NULL;
			i++;
		}
		free(list->mtx);
		list->mtx = NULL;
		tmp = list;
		list = list->next;
		free(tmp);
		tmp = NULL;
	}
}

void	free_parser(t_parser *pars)
{
	int	i;

	i = 0;
	while (pars->tokens[i])
	{
		if (pars->tokens[i])
		{
			free (pars->tokens[i]);
			pars->tokens[i] = NULL;
		}
		i++;
	}
	free (pars->tokens);
	pars->tokens = NULL;
	free (pars->input_copy);
	pars->input_copy = NULL;
}

void	free_env4mini(t_env4mini *env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env->env[i])
		{
			free(env->env[i]);
			env->env[i] = NULL;
			i++;
		}
		free(env->env);
		env->env = NULL;
		free(env);
		env = NULL;
	}
}
