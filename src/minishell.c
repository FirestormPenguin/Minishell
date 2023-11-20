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
        execve(path, (char *const *)args, NULL);
        exit(0);
    }
}

/*funzione che builda i nodi relativi del tree partendo dalla
matrice composta da due parti, realativamente a sinistra e destra
il divisore*/
void build_tree(char **mtx, t_tree *tree)
{
    int i;
    t_tree  *tmp;

    tmp = tree;
    i = -1;
    while (mtx[++i])
    {
        insertLeft(tmp, mtx[i]);
        if (mtx[i + 1])
        {
            insertRight(tmp, mtx[i + 1]);
            i++;
        }
    }
    inorderTraversal(tree);
}

void test(char *str)
{
    char **mtx;
    int arg_count;
    t_tree *tree;
    char div[1];

    char pipe = '|';
    char space = ' ';
    char minmaj = '>';
    
    div[0] = pipe;
    if (strchr(str, pipe) != NULL)
    {
        tree = create_tree(div);
        mtx = tokenizer(str, &arg_count, div);
    }
    else
    {
        return ;
    }
    build_tree(mtx, tree);
    // insertLeft(tree, mtx[0]);
    // insertRight(tree, mtx[1]);
    // inorderTraversal(tree);
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
