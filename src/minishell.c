/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirko <mirko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/11/29 18:09:03 by mirko            ###   ########.fr       */
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

void level_order_insert(t_tree **root, char **mtx, int *i)
{
    Queue *queue;
	t_tree *current;

	queue = create_queue();
    if (*root == NULL)
	{
        *root = create_node(mtx[*i]);
        (*i)++;
        enqueue(queue, *root);
    }

    while (1)
	{
        current = dequeue(queue);

        if (current == NULL)
            break; // Tutti i nodi esplorati
        if (current->left == NULL && mtx[*i] != NULL)
		{
            current->left = create_node(mtx[*i]);
            (*i)++;
            enqueue(queue, current->left);
        }
        if (current->right == NULL && mtx[*i] != NULL)
		{
            current->right = create_node(mtx[*i]);
            (*i)++;
            enqueue(queue, current->right);
        }
    }
	destroy_queue(queue);
}

t_tree *build_tree(char **mtx)
{
	t_tree *root = NULL;
	int i;

	i = 0;
	level_order_insert(&root, mtx, &i);

	return (root);
}

char **reorder_mtx(char **mtx, int count, char *div)
{
    char **tmp;
    int i;

    tmp = (char**)malloc((count + 2) * sizeof(char*));
    tmp[0] = div;
    i = -1;
    while (tmp[++i])
    {
        tmp[i + 1] = mtx[i];
    }
    return (tmp);
}

void tokenize_string(char *str)
{
    char **mtx;
    int arg_count;
    t_tree *tree;
    char div[1];
    int i;
    
    div[0] = '|';
    i = -1;
    if (strchr(str, '|') != NULL)
        div[0] = '|';
    else if (strchr(str, '>') != NULL)
         div[0] = '>';
    else if (strchr(str, '<') != NULL)
        div[0] = '<';
    else
        return;
    mtx = tokenizer(str, &arg_count, div);
    mtx = reorder_mtx(mtx, arg_count, div);
    tree = build_tree(mtx);
    
    inorderTraversal(tree);
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
            tokenize_string(inputString);
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
