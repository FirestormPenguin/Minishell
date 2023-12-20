# include "../include/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*current_str;
	char		*token_start;

	if (str != NULL)
		current_str = str;
	else if (current_str == NULL)
		return (NULL);

	token_start = current_str;
	while (*current_str != '\0' && ft_strchr(delim, *current_str) != NULL)
		current_str++;
	if (*current_str == '\0')
		current_str = NULL;

	token_start = current_str;
	while (*current_str != '\0' && ft_strchr(delim, *current_str) == NULL)
		current_str++;
	if (*current_str == '\0')
		current_str = (NULL);
	else
	{
		*current_str = '\0';
		current_str++;
	}
	return (token_start);
}