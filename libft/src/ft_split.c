/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:15:58 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/20 19:17:51 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static	int	count_split(char const *str, char c)
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
