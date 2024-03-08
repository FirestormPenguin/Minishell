/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:08:33 by mivendit          #+#    #+#             */
/*   Updated: 2024/03/08 22:04:10 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strtok(char *str, const char *delim);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isstrdigit(char *str);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	ft_putstr(char *s);
void	ft_qsort(char **arr, int low, int high);
char	*ft_itoa(int n);
int		ft_isalpha(int c);
void	*ft_realloc(void *old_pointer, size_t size, int old_dim, int new_dim);
#endif
