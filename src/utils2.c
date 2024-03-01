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

void	free_all_generic(char *path, char **args)
{
	if (args)
		free_double_pointer(args);
	if (path)
		free (path);
	if (access("HERE_DOC", F_OK) != -1)
		unlink("HERE_DOC");
}

void	free_exit(int exit_code, t_grb_collector *grb_ptr)
{
	// t_struct_pointers	*ptr_struct;

	// ptr_struct = (t_struct_pointers *)struct_box(NULL, SET_ACTUAL);
	// if (ptr_struct)
	// {
		// free_list(ptr_struct->list_ptr);
		// free_parser(ptr_struct->parser_ptr);
		// free_env4mini(ptr_struct->env_ptr);
	// }
	free_list(grb_ptr->list_ptr);
	free_parser(grb_ptr->parser_ptr);
	free_env4mini(grb_ptr->env_ptr);
	free (grb_ptr);
	exit(exit_code);
}
