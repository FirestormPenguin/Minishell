/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:33 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/08 10:20:52 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_stdin_stdout(t_process *proc)
{
	dup2(proc->saved_stdout, STDOUT_FILENO);
	dup2(proc->saved_stdin, STDIN_FILENO);
}

int	check_error_redirection(t_list *list)
{
	while (list)
	{
		if (list->type != WORD && check_type(list->mtx[0]) != WORD)
		{
			printf("parse error near '%s'\n", list->mtx[0]);
			return (1);
		}
		else if (ft_strcmp(list->mtx[0], "\n") == 0 || ft_strcmp(list->mtx[0], " ") == 0 || ft_strcmp(list->mtx[0], "") == 0)
		{
			printf("parse error near '%s'\n", list->mtx[0]);
			return (1);
		}
		list = list->next;
	}
	return (0);
}

int setup_redirection(t_list *list, t_process *proc)
{
	while (list)
	{
		if (list->type != WORD && list->type != PIPE)
			redirections(list, proc);
		else if (list->type == PIPE)
			return (0);
		list = list->next;
	}
	return (0);
}

void init_vars(char **path, char ***args, int *i)
{
    *path = malloc(sizeof(char) * 50);
    *args = calloc(50, sizeof(char *));  /* usato calloc per allocare memoria ( == malloc) ma in più inizializza i point a NULL */
    *i = 0;
    strcpy(*path, "/bin/");
}

/* mentre testavo quella che ora è una stupida funzione cd, se tornavo 
inidetro fino alla directory "/" e uscivo con la mia free_exit andava 
in segfault, il problema era che tentavo di accedere a memoria non 
allocata visto che fill_args prima allocava 50 caratteri, ora alloca 
la lunghezza della str + 1 caratteri, e funziona*/

/* char	**fill_args(t_list *list, char **args, int i)
{
	int j;
	
	j = 0;
	while (list->mtx[i])
		{
			args[j] = malloc (sizeof(char) * 50);
			strcpy(args[j], list->mtx[i]);
			i++;
			j++;
		}
	args[j] = NULL;
	return (args);
} */

char **fill_args(t_list *list, char **args, int i)
{
    int j = 0;
    while (list->mtx[i])
    {
        args[j] = malloc(strlen(list->mtx[i]) + 1);
        if (!args[j]) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        strcpy(args[j], list->mtx[i]);
        i++;
        j++;
    }
    args[j] = NULL;
    return args;
}

int	check_mtx(t_list *list, t_process *proc, int i)
{
	if (!list->mtx[i])
	{
		reset_stdin_stdout(proc);
		free_all_generic(proc->path, proc->args);
		return (1);
	}
	return (0);
}

