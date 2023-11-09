/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/11/09 17:33:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

void exe(char *str)
{
    pid_t   pid;
    int     status;
    char    path[50] = "/bin/";
    char    *args[] = {str, NULL};
    
    /*con strcat unisco al path il comando
    NOTA: non si puo' usare strcat, da mettere ft_strcat*/
    strcat(path, str);
    /*forka il processo creando un figlio*/
    pid = fork();
    /*if is in pid, siamo nel processo padre
    che tramite wait attende che i figli si chiudano,
    else siamo nel processo figlio, i due processi
    lavorano in contemporanea*/
    if (pid)
    {
        //printf("%d\n", pid);
        waitpid(-1, &status, WUNTRACED);
        //printf("%d\n", status);
    }
    else
    {
        /*execve esegue un comando di bash tramite path (/bin/...)
        e comando di per se (ls, pwd, etc), args normalmente
        contiene il comando + flag (opzionale) + NULL*/
        execve(path, args, NULL);
        exit(0);
    }
    
}

void getInput()
{
    char *inputString;
    
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
            exe(inputString);
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
