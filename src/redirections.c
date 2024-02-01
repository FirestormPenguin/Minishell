/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/01 17:55:06 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

void	input(t_list *list)
{
	int input_fd;

	input_fd = open(list->mtx[0], O_RDONLY);
	if (input_fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return ;
	}
	close(input_fd);
}

void	redirections(t_list *list)
{
	if (list->type == IN && list->mtx[0])
	{
		input (list);
	}
	else if (list->type == OUT && list->mtx[0])
	{
		
	}
	else if (list->type == DOUBLE_OUT && list->mtx[0])
	{
		
	}
	else if (list->type == HERE_DOC && list->mtx[0])
	{
		
	}
	else if (list->type == PIPE && list->mtx[0])
	{
		
	}
	else
		printf ("redirection/pipe error!\n");
}
