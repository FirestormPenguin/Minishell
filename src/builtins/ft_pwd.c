/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:36:12 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/06 15:36:12 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	pwd[4096];

	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
	else
		printf("minshell: the path is broken");
	return (0);
}
