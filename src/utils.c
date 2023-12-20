#include <../include/minishell.h>

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dstsize > 0)
// 	{
// 		while (src[i] && i < (dstsize -1))
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = 0;
// 	}
// 	while (src[i])
// 		i++;
// 	return (i);
// }

// size_t	ft_strlen(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char		*str;

// 	if (!s)
// 		return (NULL);
// 	if (ft_strlen(s) < start)
// 		len = 0;
// 	if (ft_strlen(s + start) < len)
// 		len = ft_strlen(s + start);
// 	str = malloc (sizeof(char) * (len + 1));
// 	if (!str)
// 		return (NULL);
// 	ft_strlcpy(str, s + start, len + 1);
// 	return (str);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t	i;
// 	size_t	len;
// 	char	**split;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	split = (char **)malloc(sizeof(char *) * (count_split(s, c) + 1));
// 	if (!split)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			len = 0;
// 			while (*s && *s != c && ++len)
// 				s++;
// 			split[i++] = ft_substr(s - len, 0, len);
// 		}
// 		else
// 			s++;
// 	}
// 	split[i] = NULL;
// 	return (split);
// }

// char	*ft_strdup(const char *s1)
// {
// 	char	*str;
// 	size_t	i;

// 	str = (char *) malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	str[i] = 0;
// 	return (str);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (char)c)
// 		{
// 			return ((char *)(s + i));
// 		}		
// 		i++;
// 	}
// 	if (s[i] == (char)c)
// 	{	
// 		return ((char *)(s + i));
// 	}	
// 	return (NULL);
// }

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	i;
// 	int		ret;

// 	ret = 0;
// 	i = 0;
// 	while (s1[i] || s2[i])
// 	{
// 		if ((!s1[i] && s2[i]) || (s1[i] && !s2[i]))
// 			return(1);
// 		if (cmp_char(s1[i], s2[i]) != 0)
// 			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_strtok(char *str, const char *delim)
// {
// 	static char	*current_str;
// 	char		*token_start;

// 	if (str != NULL)
// 		current_str = str;
// 	else if (current_str == NULL)
// 		return (NULL);

// 	token_start = current_str;
// 	while (*current_str != '\0' && ft_strchr(delim, *current_str) != NULL)
// 		current_str++;
// 	if (*current_str == '\0')
// 		current_str = NULL;

// 	token_start = current_str;
// 	while (*current_str != '\0' && ft_strchr(delim, *current_str) == NULL)
// 		current_str++;
// 	if (*current_str == '\0')
// 		current_str = (NULL);
// 	else
// 	{
// 		*current_str = '\0';
// 		current_str++;
// 	}
// 	return (token_start);
// }

// static int	cmp_char(char c1, char c2)
// {
// 	if ((unsigned char)c1 != (unsigned char)c2)
// 		return ((unsigned char)c1 - (unsigned char)c2);
// 	return (0);
// }

// int	count_split(char const *str, char c)
// {
// 	size_t	i;
// 	size_t	total;

// 	i = 0;
// 	total = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != c)
// 		{
// 			total++;
// 			while (str[i] && str[i] != c)
// 				i++;
// 		}
// 		else
// 		i++;
// 	}
// 	return (total);
// }