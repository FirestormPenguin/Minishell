/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/11/10 17:12:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

char    **split_args(char *str)
{
    char    **args = ft_split(str, ' ');
    
    args = ft_split(str, ' ');
    args[count_split(str, ' ') + 1] = NULL;
    int i = -1;
    return (args);
}

void exe(char *str)
{
    pid_t   pid;
    int     status;
    char    path[50] = "/bin/";
    char    **mtx;
    char    **args;
    
    mtx = split_args(str);
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



void check_string(char *str)
{
    char    *tmp;
    int     i;
    int     j;
    int     l;
    
    i = -1;
    j = -1;
    while (*str)
    {
        l = -1;
        if (*str != ' ' || *str!= '\0')
        {
            while(++l <= i)
            {
                tmp[l] = str[++j];
                printf("%c\n", tmp[j]);
            }
            tmp[j + 1] = '\0';
            printf("%s\n", tmp);
            exe(tmp);
            i++;
        }
    }
}

void getInput()
{
    char *inputString;
    char *exeString;
    
    while (1)
    {
        /*utilizzo readline per prendere da terminale l'input*/
        inputString = readline("<Minishell> ");      
        /*if inputString is NULL (cntrl + D) break*/    
        if (!inputString)
            break;
        /*if inputString is "exit", break*/
        if (strcmp(inputString, "exit") == 0)
        {
            free(inputString);
            break;
        }
        else
        {
            check_string(inputString);
        }
        /*aggiunge alla history il comando appena scritto*/
        add_history(inputString);
        free(inputString);
    }
}

int main(int ac, char **av, char **envp)
{
    (void) ac;
    (void) av;

    /*prende l'input da terminale*/
    getInput();
    return (0);
}
