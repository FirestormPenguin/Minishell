#include <../include/minishell.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < (dstsize -1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc (sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

int	count_split(char const *str, char c)
{
	size_t	i;
	size_t	total;

	i = 0;
	total = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			total++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
		i++;
	}
	return (total);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**split;

	if (!s)
		return (NULL);
	i = 0;
	split = (char **)malloc(sizeof(char *) * (count_split(s, c) + 1));
	if (!split)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			split[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	split[i] = NULL;
	return (split);
}