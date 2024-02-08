# include "../include/libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = malloc(num * size);
	if (ptr)
		ft_memset(ptr, 0, num * size);

	return (ptr);
}