/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 00:21:37 by mivendit          #+#    #+#             */
/*   Updated: 2024/03/03 00:37:45 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_realloc(void *old_pointer, size_t element_size, int old_dim, int new_dim)
{
	char		*new_pointer;
	size_t		index;

	new_pointer = (char *)malloc(element_size * new_dim);
	if (!new_pointer)
		return (NULL);
	index = 0;
	while (index < element_size * new_dim)
	{
		if (index < element_size * old_dim)
			new_pointer[index] = ((char *) old_pointer)[index];
		else
			new_pointer[index] = 0;
		index++;
	}
	free(old_pointer);
	return ((void *) new_pointer);
}
