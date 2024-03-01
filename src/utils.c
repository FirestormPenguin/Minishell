/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:27:21 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/26 11:05:32 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	*struct_box(t_struct_pointers *ptr_struct, int operation)
// {
// 	static t_struct_pointers	*this_ptr_struct;

// 	this_ptr_struct = NULL;
// 	if (operation == SET_ACTUAL)
// 	{
// 		this_ptr_struct = ptr_struct;
// 		return (NULL);
// 	}
// 	// else if (operation == GET_ARGS)
// 	// 	return (this_ptr_struct->args_ptr);
// 	else if (operation == GET_LIST)
// 		return (this_ptr_struct->list_ptr);
// 	else if (operation == GET_PARSER)
// 		return (this_ptr_struct->parser_ptr);
// 	else if (operation == GET_ENV)
// 		return (this_ptr_struct->env_ptr);
// 	return (NULL);
// }

// void	free_args(t_args *args)
// {
// 	if (args)
// 	{
// 		if (args->str)
// 			free(args->str);
// 		free(args);
// 	}
// }

void	free_list(t_list *list)
{
	int	i;

	i = 0;
	if (list)
	{
		while (list->mtx[i])
		{
			free(list->mtx[i]);
			i++;
		}
		free(list->mtx);
		free(list);
	}
}

void	free_parser(t_parser *pars)
{
	int	i;

	i = 0;
	while (pars->tokens[i])
	{
		if (pars->tokens[i])
			free (pars->tokens[i]);
		i++;
	}
	if (pars->tokens)
		free (pars->tokens);
	if (pars->input_copy)
		free (pars->input_copy);
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
			i++;
		}
		free(env->env);
		free(env);
	}
}
