#include "../../include/minishell.h"

void write_into_fd(char *str)
{
	int	fd;
	size_t len;

	fd = open("HERE_DOC", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	len = strlen(str);
	write(fd, str, len);
	close (fd);
}
