#include "../../include/minishell.h"

void ft_unset_env(char *name, t_env4mini *all)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (all->env[i])
	{
		if (ft_strncmp(all->env[i], name, ft_strlen(name)) == 0)
		{
			free(all->env[i]);
			j = i;
			while (all->env[j])
			{
				all->env[j] = all->env[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

void ft_setenv(char *name, char *value, t_env4mini *all)
{
	int i;
	char *tmp;

	i = 0;
	while (all->env[i])
	{
		if (ft_strncmp(all->env[i], name, ft_strlen(name)) == 0)
		{
			tmp = all->env[i];
			all->env[i] = ft_strjoin(name, "=");
			all->env[i] = ft_strjoin(all->env[i], value);
			free(tmp);
			return ;
		}
		i++;
	}
	all->env[i] = ft_strjoin(name, "=");
	all->env[i] = ft_strjoin(all->env[i], value);
	all->env[i + 1] = NULL;
}

void ft_export(char **args, t_env4mini *all) 
{
    int i;
    int j;
    char *name;
    char *value;
    char **env_copy;

    i = 1;
    if (!args[i])
    {
        // Crea una copia dell'array delle variabili d'ambiente
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

        // Ordina la copia e la stampa
        ft_qsort(env_copy, 0, i - 1);
        i = 0;
        while (env_copy[i])
        {
            ft_putstr(env_copy[i]);
            ft_putstr("\n");
            free(env_copy[i]); // Libera la memoria allocata per la copia
            i++;
        }
        free(env_copy); // Libera la memoria allocata per l'array di copia
        return ;
    }

    while (args[i])
    {
        j = 0;
        while (args[i][j] && args[i][j] != '=')
            j++;
        if (args[i][j] == '=')
        {
            name = ft_substr(args[i], 0, j);
            value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
            ft_setenv(name, value, all);
            free(name);
            free(value);
        }
        else
        {
            ft_setenv(args[i], "", all);
        }
        i++;
    }
}
