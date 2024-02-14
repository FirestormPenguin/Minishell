# include "../include/libft.h"

static int  ft_intlen(int n)
{
	int len;

	len = 0;
	if (n <= 0)
	{
		len++;
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char    *ft_itoa(int n)
{
	char    *str;
	int     len;
	long    nbr;

	nbr = n;
	len = ft_intlen(nbr);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr >= 10)
	{
		len--;
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[len - 1] = nbr % 10 + '0';
	return (str);
}
