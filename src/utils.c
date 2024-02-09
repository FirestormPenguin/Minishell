/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:27:21 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/09 14:39:12 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*struct_box(t_struct_pointers *ptr_struct, int operation)
{
    static t_struct_pointers	*this_ptr_struct;

	this_ptr_struct = NULL;
    if (operation == SET_ACTUAL)
    {
        this_ptr_struct = ptr_struct;
        return (NULL);
    }
    else if (operation == GET_ARGS)
        return (this_ptr_struct->args_ptr);
    else if (operation == GET_LIST)
        return (this_ptr_struct->list_ptr);
    else if (operation == GET_PARSER)
        return (this_ptr_struct->parser_ptr);
    else if (operation == GET_ENV)
        return (this_ptr_struct->env_ptr);
    return (NULL);
}

void	free_all_generic(char *path, char **args)
{
	if (args)
		free (args);
	if (path)
		free (path);
    if (access("HERE_DOC", F_OK) != -1)
        unlink("HERE_DOC");
}

void	free_args(t_args *args)
{
    if (args)
	{
        if (args->str)
            free(args->str);
        free(args);
    }
}

void	free_list(t_list *list)
{
	int i;

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

void	free_parser(t_parser *parser)
{
	int	i;

	i = 0;
    if (parser)
	{
        if (parser->input_copy)
            free(parser->input_copy);
        if (parser->tokens)
		{
			while(parser->tokens[i])
			{
				free(parser->tokens[i]);
				i++;
			}
            free(parser->tokens);
        }
        free(parser);
    }
}

void	free_env4mini(t_env4mini *env)
{
	int i;

	i = 0;
    if (env)
	{
		while(env->env[i])
		{
			free(env->env[i]);
			i++;
		}
        free(env->env);
        free(env);
    }
}

void free_exit(int exit_code)
{
	t_struct_pointers *ptr_struct;

	ptr_struct = (t_struct_pointers *)struct_box(NULL, SET_ACTUAL);
    if (ptr_struct)
	{
        free_args(ptr_struct->args_ptr);
        free_list(ptr_struct->list_ptr);
        free_parser(ptr_struct->parser_ptr);
        free_env4mini(ptr_struct->env_ptr);
    }
    exit(exit_code);
}
