#include "../../include/minishell.h"

void	redirections(t_list *list, t_process *proc)
{
	if (list->type == IN && list->mtx[0])
		input(list->mtx[0], proc);
	if (list->type == OUT && list->mtx[0])
		output(list->mtx[0], proc);
	if (list->type == DOUBLE_OUT && list->mtx[0])
		append(list->mtx[0], proc);
	else if (list->type == HERE_DOC && list->mtx[0])
		here_doc(list->mtx[0], proc);
}

void write_into_fd(char *str)
{
	int	fd;
	size_t len;

	fd = open("HERE_DOC", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	len = strlen(str);
	write(fd, str, len);
	close (fd);
}
