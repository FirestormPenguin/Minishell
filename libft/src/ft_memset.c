# include "../include/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr_b;

	i = 0;
	ptr_b = (unsigned char *)b;
	while (i < len)
		ptr_b[i++] = (unsigned char)c;
	return (b);
}