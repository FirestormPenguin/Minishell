/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:38:22 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/27 10:26:36 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	increment_shlvl(t_env4mini *all)
{
	char	*sh_lvl_str;
	int		sh_lvl;

	sh_lvl = ft_atoi(ft_getenv("SHLVL", all->env));
	sh_lvl++;
	sh_lvl_str = ft_itoa(sh_lvl);
	ft_setenv("SHLVL", sh_lvl_str, all);
	return ;
}
