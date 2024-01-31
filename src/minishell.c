/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2024/01/31 15:17:18 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

void exe(t_list *list)
{
	pid_t	pid;
	int		status;
	char	*path;
	int		i;

	path = malloc (sizeof(char) * 50);
	while (list)
	{
		i = 0;
		strcpy(path, "/bin/");
		if (list->type != WORD && check_type(list->mtx[i]) != WORD)
		{
			printf("parse error near '%s'\n", list->mtx[i]);
		}
		else
		{
			strcat(path, list->mtx[0]);
			pid = fork();
			if (pid)
			{
				waitpid(-1, &status, WUNTRACED);
			}
			else
			{
				execve(path, (char *const *)list->mtx, NULL);
				exit(0);
			}
		}
		list = list->next;
	}
	free (path);
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
