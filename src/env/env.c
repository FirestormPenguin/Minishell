/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 00:00:04 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/06 00:00:04 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	malloc_perror(void)
{
	perror("Memory allocation error");
	exit(1);
}

int	copy_env(char **env, t_env4mini *all)
{
	int	env_size;
	int	i;

	i = 0;
	env_size = 0;
	while (env[env_size] != NULL)
		env_size++;
	all->env = (char **)malloc((env_size + 1) * sizeof(char *));
	if (all->env == NULL)
		malloc_perror();
	while (env[i] != NULL)
	{
		all->env[i] = ft_strdup(env[i]);
		if (all->env[i] == NULL)
			malloc_perror();
		i++;
	}
	all->env[i] = NULL;
	return (1);
}

void	free_env(t_env4mini *all)
{
	int	i;

	i = 0;
	while (all->env[i] != NULL)
	{
		free(all->env[i]);
		i++;
	}
	free(all->env);
}

void	print_env_copy(t_env4mini *all)
{
	int	i;

	i = 0;
	while (all->env[i] != NULL)
	{
		printf("%s\n", all->env[i]);
		i++;
	}
}
