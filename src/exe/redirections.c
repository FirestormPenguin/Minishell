/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/05 15:27:41 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	input(t_list *list)
{
	int input_fd;

	input_fd = open(list->mtx[0], O_RDONLY);
	if (input_fd == -1)
		perror("open");
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("dup2");
	close(input_fd);
}

void output(t_list *list)
{
	int output_fd;

	output_fd = open(list->mtx[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		perror("open");
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(output_fd);
}

void append (t_list *list)
{
	int fd_append;

	fd_append = open(list->mtx[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_append == -1)
		perror("open");

	if (dup2(fd_append, STDOUT_FILENO) == -1)
		perror("dup2");
	close(fd_append);
}

/*da finire, non funziona*/
void here_doc(t_list *list)
{
	char *input_line;

	input_line = NULL;
	while (1)
	{
		input_line = readline("");
		if (ft_strcmp(input_line, list->mtx[0]) == 0)
			break;
		free(input_line);
	}
}

void	redirections(t_list *list)
{
	if (list->type == IN && list->mtx[0])
	{
		input (list);
	}
	else if (list->type == OUT && list->mtx[0])
	{
		output(list);
	}
	else if (list->type == DOUBLE_OUT && list->mtx[0])
	{
		append(list);
	}
	else if (list->type == HERE_DOC && list->mtx[0])
	{
		here_doc(list);
	}
	else
		printf ("redirection/pipe error!\n");
}
