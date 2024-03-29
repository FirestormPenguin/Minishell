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

void	exp_no_argument(t_env4mini *all, int index)
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
		ft_putstr("declare -x ");
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

void	norm_print_index(char **args, t_env4mini *all)
{
	printf("Mini: export: `%s': not a valid identifier\n", args[2]);
	ft_setenv(args[1], "", all);
	return ;
}

void	while_export(char **args, int i, t_env4mini *all)
{
	int	eq_ind;
	int	j;

	while (args[++i])
	{
		eq_ind = find_valid_equals(args[i]);
		if (ft_isdigit(args[i][0]) || eq_ind == 2 || !is_valid_str(args[i]))
		{
			printf("Mini: export: `%s': not a valid identifier\n", args[i++]);
			continue ;
		}
		if (eq_ind == -1)
		{
			printf("Mini: export: `%s': not a valid identifier\n", args[i]);
			ft_setenv(args[1], "", all);
		}
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (args[i][j] == '=')
			equal_case(args, all, i, j);
		else if (eq_ind == 1)
			ft_setenv(args[i], "", all);
	}
}

void	ft_export(char **args, t_env4mini *all)
{
	if (!args[1])
		exp_no_argument(all, 1);
	while_export(args, 0, all);
}
