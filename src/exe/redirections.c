/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/03/09 15:00:48 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	input(char *str)
{
	int	input_fd;

	input_fd = open(str, O_RDONLY);
	if (input_fd == -1)
		perror("open");
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror("dup2");
	close(input_fd);
}

void	output(char *str)
{
	int	output_fd;

	output_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_fd == -1)
		perror("open");
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(output_fd);
}

void	append(char *str) // to_fix (cat << m | ls) (cat < m | ls)
{
	int	fd_append;

	fd_append = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_append == -1)
		perror("open");
	if (dup2(fd_append, STDOUT_FILENO) == -1)
		perror("dup2");
	close(fd_append);
}

void	here_doc(char *str)
{
	char	*input_line;
	char	*tmp_str;

	input_line = NULL;
	tmp_str = ft_calloc(10000, sizeof(char));
	while (1)
	{
		input_line = readline("> ");
		if (ft_strcmp(input_line, str) == 0)
		{
			free(input_line);
			break ;
		}
		strcat(tmp_str, input_line);
		strcat(tmp_str, "\n");
		free(input_line);
	}
	write_into_fd(tmp_str);
	free(tmp_str);
	input("HERE_DOC");
}
