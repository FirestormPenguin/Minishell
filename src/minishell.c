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

#include "../include/minishell.h"

void	free_all(char *path, char **args)
{
	// int	i;

	// i = -1;
	// while (args[++i])
	// {
	// 	if (args[i])
	// 		free(args[i]);
	// }
	free (args);
	free(path);
}

void exe(t_list *list, t_env4mini *all) {
    pid_t   pid;
    int     status;
    char    *path;
    int		i;
	int		j;
	char	**args;
	int		saved_stdout;
	int		saved_stdin;
    
    saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
    while (list) {
        path = malloc (sizeof(char) * 50);
		args = malloc (sizeof(char *) * 50);
        i = 0;
        j = 0;
        strcpy(path, "/bin/");
        if (list->type != WORD && check_type(list->mtx[i]) != WORD) {
            printf("parse error near '%s'\n", list->mtx[i]);
            return ;
        } 
        if (list->type != WORD && list->type != PIPE)
		{
			redirections(list);
			i++;
		}
        if (!list->mtx[i])
		{
			free_all(path, args);
			return ;
		}
        strcat(path, list->mtx[0]);
        while (list->mtx[i])
		{
			args[j] = malloc (sizeof(char) * 50);
			strcpy(args[j], list->mtx[i]);
			i++;
			j++;
		}
        args[j] = NULL;
        
        pid = fork();
        if (pid) {
            waitpid(-1, &status, WUNTRACED);
			dup2(saved_stdout, STDOUT_FILENO);
			dup2(saved_stdin, STDIN_FILENO);
			list = list->next;
			free_all(path, args);
        }
        else
		{
			execve(path, (char *const *)args, all->env);
			//perror("execve");
			break ;
		}
    }
    close(saved_stdout);
	close(saved_stdin);
}

void getInput(t_env4mini *all) {
    char *inputString;
    t_list *node;

    while (1) {
        inputString = readline("Minishell: ");
        if (!inputString)
            break;
        if (!ft_strcmp(inputString, "exit")) 
        {
            free(inputString);
            break;
        } 
        else
        {
        node = tokenize_string(inputString);
        add_history(inputString);
        exe(node, all);
        }
        free(inputString);
    }
}

int main(int ac, char **av, char **envp) {
	(void)ac;
	(void)av;
	t_env4mini all;
	
	copy_env(envp, &all);
	//print_env_copy(&all);
	getInput(&all);

    //fix: Creare funzione separata
    int i = 0;
    while (all.env[i] != NULL) {
        free(all.env[i]);
        i++;
    }
    free(all.env);

    return 0;
}

