/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/12 17:04:39 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	input(char *str)
{
	int input_fd;

	input_fd = open(str, O_RDONLY);
	if (input_fd == -1)
		perror("open");
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("dup2");
	close(input_fd);
}

void output(char *str)
{
	int output_fd;

	output_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		perror("open");
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(output_fd);
}

void append (char *str)
{
	int fd_append;

	fd_append = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_append == -1)
		perror("open");
	if (dup2(fd_append, STDOUT_FILENO) == -1)
		perror("dup2");
	close(fd_append);
}

void here_doc(char *str, t_process *proc)
{
	char	*input_line;
	char	*tmp_str;

	input_line = NULL;
	tmp_str = ft_calloc(1000, sizeof(char *));
	while (1)
	{
		input_line = readline("> ");
		if (ft_strcmp(input_line, str) == 0)
			break;
		strcat(tmp_str, input_line);
		strcat(tmp_str, "\n");
		free(input_line);
	}
	write_into_fd(tmp_str);
	input("HERE_DOC");
}

void	redirections(t_list *list, t_process *proc)
{
	reset_stdin_stdout(proc);
	if (list->type == IN && list->mtx[0])
		input (list->mtx[0]);
	else if (list->type == OUT && list->mtx[0])
		output(list->mtx[0]);
	else if (list->type == DOUBLE_OUT && list->mtx[0])
		append(list->mtx[0]);
	else if (list->type == HERE_DOC && list->mtx[0])
		here_doc(list->mtx[0], proc);
	else
		printf ("redirection/pipe error!\n");
}
