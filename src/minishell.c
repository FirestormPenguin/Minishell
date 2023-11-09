/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/11/09 15:45:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

void exe(char *str)
{
    pid_t   pid;
    int     status;
    char    path[50] = "/bin/";
    char    *args[] = {str, NULL};
    
    strcat(path, str);
    pid = fork();
    if (pid)            //if is in pid, siamo nel processo padre
    {
        printf("%d\n", pid);
        waitpid(-1, &status, WUNTRACED);    //wait qualunque figlio esistente
        printf("%d\n", status);
    }
    else                //else siamo nel processo figlio
    {
        execve(path, args, NULL);
        exit(0);
    }
    
}

void getInput()
{
    char *inputString;
    
    while (1)
    {
        inputString = readline("<Minishell> ");          //utilizzo readline per prendere da terminale l'input
        if (!inputString)                               //if inputString is NULL (cntrl + D) break
            break;
        if (strcmp(inputString, "exit") == 0)           //if inputString is "exit", break
        {
            free(inputString);
            break;
        }
        else
            exe(inputString);
        add_history(inputString);                       //aggiunge alla history il comando appena scritto
        free(inputString);
    }
}

int main(int ac, char **av, char **envp)
{
    (void) ac;
    (void) av;

    getInput();         //prende l'input da terminale
    return (0);
}
