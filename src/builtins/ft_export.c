/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:16:05 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/20 00:16:05 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exp_no_argument(char **args, t_env4mini *all, int index)
{
	char	**env_copy;

	while (all->env[index])
		index++;
	env_copy = malloc((index + 1) * sizeof(char *));
	index = 0;
	while (all->env[index])
	{
		env_copy[index] = strdup(all->env[index]);
		index++;
	}
	env_copy[index] = NULL;
	ft_qsort(env_copy, 0, index - 1);
	index = 0;
	while (env_copy[index])
	{
		ft_putstr(env_copy[index]);
		ft_putstr("\n");
		free(env_copy[index]);
		index++;
	}
	free(env_copy);
	return ;
}

void	equal_case(char **args, t_env4mini *all, int i, int j)
{
	char	*name;
	char	*value;
	char	*new_value_appeand;
	char	*old_value_appeand;

	if (j > 0 && args[i][j - 1] == '+')
	{
		name = ft_substr(args[i], 0, j - 1);
		value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
		old_value_appeand = ft_getenv(name, all->env);
		new_value_appeand = ft_strjoin(old_value_appeand, value);
		ft_setenv(name, new_value_appeand, all);
		free(name);
		free(value);
		free(new_value_appeand);
	}
	else
	{
		name = ft_substr(args[i], 0, j);
		value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
		ft_setenv(name, value, all);
		free(name);
		free(value);
	}
}

void	ft_export(char **args, t_env4mini *all)
{
	int	i;
	int	j;
	int	equals_index;

	i = 1;
	if (!args[i])
		exp_no_argument(args, all, i);
	while (args[i])
	{
		equals_index = find_valid_equals(args[i]);
		if (equals_index == -1)
		{
			printf("Mini: export: `%s': not a valid identifier\n", args[2]);
			ft_setenv(args[1], "", all);
			return ;
		}
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (args[i][j] == '=')
			equal_case(args, all, i, j);
		else if (equals_index == 1)
			ft_setenv(args[i], "", all);
		i++;
	}
}
