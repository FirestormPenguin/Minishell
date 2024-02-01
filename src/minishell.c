/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/02/01 18:08:47 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

void	free_all(char *path, char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (args[i])
			free(args[i]);
	}
	free (args);
	free(path);
}

void exe(t_list *list)
{
	pid_t	pid;
	int		status;
	char	*path;
	int		i;
	int		j;
	char	**args;

	path = malloc (sizeof(char) * 50);
	args = malloc (sizeof(char *) * 50);
	while (list)
	{
		i = 0;
		j = 0;
		strcpy(path, "/bin/");
		if (list->type != WORD && check_type(list->mtx[i]) != WORD)
		{
			printf("parse error near '%s'\n", list->mtx[i]);
			return ;
		}
		if (list->type != WORD)
		{
			redirections(list);
			i++;
		}
		if (!list->mtx[i])
		{
			free_all(path, args);
			return ;
		}
		strcat(path, list->mtx[i]);
		while (list->mtx[i])
		{
			args[j] = malloc (sizeof(char) * 50);
			strcpy(args[j], list->mtx[i]);
			i++;
			j++;
		}
		args[j] = NULL;
		pid = fork();
		if (pid)
		{
			waitpid(-1, &status, WUNTRACED);
		}
		else
		{
			execve(path, (char *const *)args, NULL);
			exit(0);
		}
		list = list->next;
	}
	free_all(path, args);
}

void getInput()
{
	char *inputString;
	t_list *node;

	while (1)
	{
		inputString = readline("Minishell: ");
		if (!inputString)
			break;
		if (ft_strcmp(inputString, "exit") == 0)
		{
			free(inputString);
			break;
		}
		else
		{
			node = tokenize_string(inputString);
			add_history(inputString);
			exe(node);
		}
		free(inputString);
	}
}

int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	getInput();
	return (0);
}
