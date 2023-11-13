/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/11/13 15:16:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

char** tokenizer(char *input, int *token_count)
{
    char    *input_copy;
    int     count;
    char    *token;
    char    **tokens;
    int     i;
    
    count = 0;
    i = 0;
    input_copy = ft_strdup(input);
    token = ft_strtok(input_copy, " \t");
    while (token != NULL)
    {
        count++;
        token = ft_strtok(NULL, " \t");
    }
    tokens = (char**)malloc((count + 1) * sizeof(char*));
    token = ft_strtok(input, " \t");
    while (token != NULL)
    {
        tokens[i] = ft_strdup(token);
        if (tokens[i] == NULL)
            exit(1);
        i++;
        token = ft_strtok(NULL, " \t");
    }
    tokens[i] = NULL;
    *token_count = count;
    free(input_copy);
    return (tokens);
}

void exe(char *str)
{
    pid_t   pid;
    int     status;
    char    path[50] = "/bin/";
    char    **mtx;
    char    **args;
    int     arg_count;
    
    mtx = tokenizer(str, &arg_count);
    args = mtx;
    strcat(path, mtx[0]);
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
}

void getInput()
{
    char *inputString;
    
    while (1)
    {
        inputString = readline("<Minishell> ");         
        if (!inputString)
            break;
        if (ft_strcmp(inputString, "exit") == 0)
        {
            free(inputString);
            break;
        }
        else
        {
            add_history(inputString);
            exe(inputString);
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
