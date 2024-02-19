#include "../../include/minishell.h"

void ft_unset_env(char **args, t_env4mini *all)
{
	int i = 1;
	while (args[i])
	{
		int j = 0;
		while (all->env[j])
		{
			if (ft_strncmp(all->env[j], args[i], ft_strlen(args[i])) == 0)
			{
				free(all->env[j]);
				while (all->env[j])
				{
					all->env[j] = all->env[j + 1];
					j++;
				}
				break;
			}
			j++;
		}
		i++;
	}
}

void ft_setenv(char *name, char *value, t_env4mini *all)
{
	int i;

	i = 0;
	while (all->env[i])
	{
		if (ft_strncmp(all->env[i], name, ft_strlen(name)) == 0)
		{
			all->env[i] = ft_strjoin(name, "=");
			all->env[i] = ft_strjoin(all->env[i], value);
			return ;
		}
		i++;
	}
	all->env[i] = ft_strjoin(name, "=");
	all->env[i] = ft_strjoin(all->env[i], value);
	all->env[i + 1] = NULL;
}

int find_valid_equals(char *str)
{
	int	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i > 0 && str[i - 1] != ' ')
				return 0;
		}
		i++;
	}
	return -1;
}

void ft_export(char **args, t_env4mini *all)
{
	int i;
	int j;
	char *name;
	char *value;
	char **env_copy;
	char *new_value_appeand;
	char *old_value_appeand;

	i = 1;
	if (!args[i])
	{
		while (all->env[i])
			i++;
		env_copy = malloc((i + 1) * sizeof(char *));
		i = 0;
		while (all->env[i])
		{
			env_copy[i] = strdup(all->env[i]);
			i++;
		}
		env_copy[i] = NULL;
		ft_qsort(env_copy, 0, i - 1);
		i = 0;
		while (env_copy[i])
		{
			ft_putstr(env_copy[i]);
			ft_putstr("\n");
			free(env_copy[i]);
			i++;
		}
		free(env_copy);
		return ;
	}

	while (args[i])
	{
		int equals_index = find_valid_equals(args[i]);
		if (equals_index == -1)
		{
			printf("Minishell: export: `%s': not a valid identifier\n", args[2]);
			return ;
		}
		//printf("args[%d]%s\n", i, args[i]);
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		if (args[i][j] == '=')
		{
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
		else
			ft_setenv(args[i], "", all);
		i++;
	}
}
