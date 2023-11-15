/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirko <mirko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/11/14 14:29:32 by mirko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

void exe(char *str)
{
    pid_t   pid;
    int     status;
    char    path[50] = "/bin/";
    char    **mtx;
    char    **args;
    int     arg_count;
    char    *div;
    
    int i = -1;
    div = " \t\n|";
    mtx = tokenizer(str, &arg_count, div);
    args = mtx;
    strcat(path, mtx[0]);
    pid = fork();
    if (pid)
    {
        waitpid(-1, &status, WUNTRACED);
    }
    else
    {
        //execve(path, (char *const *)args, NULL);
        exit(0);
    }
}

void test(char *str)
{
    char **mtx;
    int i;
    int arg_count;
    t_tree *tmp;

    char pipe = '|';
    char space = ' ';
    char minmaj = '>';
    
    if (strchr(str, pipe) != NULL)
    {
        tmp = create_tree("|");
        mtx = tokenizer(str, &arg_count, "|");
    }
    else
    {
        return ;
    }
    i = -1;
    while(mtx[++i])
        printf("%s\n", mtx[i]);
    //if (strchr(str, space) != NULL)
    mtx = tokenizer(str, &arg_count, " ");
    insertLeft(tmp, mtx[0]);
    insertRight(tmp, mtx[1]);
     inorderTraversal(tmp);
}

void getInput()
{
    char *inputString;
   
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
            test(inputString);
            add_history(inputString);
            //exe(inputString);
            //printf("%s: command not found\n", inputString);
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
