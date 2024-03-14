/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:27:21 by egiubell          #+#    #+#             */
/*   Updated: 2024/03/15 00:11:46 by egiubell         ###   ########.fr       */
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
	free_list(grb_ptr->list_ptr);
	free_env4mini(grb_ptr->env_ptr);
	free(grb_ptr->proc_ptr->path);
	free_double_pointer(grb_ptr->proc_ptr->args);
	free(grb_ptr);
	grb_ptr = NULL;
	exit(exit_code);
}
