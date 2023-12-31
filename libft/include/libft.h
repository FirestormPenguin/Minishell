#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strtok(char *str, const char *delim);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *b, int c, size_t len);

#endif
