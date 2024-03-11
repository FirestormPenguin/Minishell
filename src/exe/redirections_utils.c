/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/03/08 21:54:31 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirections(t_list *list)
{
	int	status;

	status = 0;
	if (list->type == IN && list->mtx[0])
	{
		status |= 0x2;
		input(list->mtx[0]);
	}
	if (list->type == OUT && list->mtx[0])
	{
		status |= 0x1;
		output(list->mtx[0]);
	}
	if (list->type == DOUBLE_OUT && list->mtx[0])
	{
		status |= 0x1;
		append(list->mtx[0]);
	}
	if (list->type == HERE_DOC && list->mtx[0])
	{
		status |= 0x2;
		here_doc(list->mtx[0]);
	}
	return (status);
}

void	write_into_fd(char *str)
{
	int		fd;
	size_t	len;

	fd = open("HERE_DOC", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	len = strlen(str);
	write(fd, str, len);
	close (fd);
}
