/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirko <mirko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:05 by codespace         #+#    #+#             */
/*   Updated: 2023/11/14 14:36:12 by mirko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_tree
{
   char *data;
   struct s_tree *left;
   struct s_tree *right;
}     t_tree;

char     **ft_split(char const *s, char c);
int      count_split(char const *str, char c);
char	   *ft_strdup(const char *s1);
char	   *ft_strchr(const char *s, int c);
int      ft_strcmp(const char *s1, const char *s2);
char*    ft_strtok(char* str, const char* delim);

t_tree   *create_tree(char *value);
t_tree*  insertLeft(t_tree* root, char *value);
t_tree*  insertRight(t_tree* root, char *value);
void     inorderTraversal(t_tree *root);

char     **tokenizer(char *input, int *token_count, char *div);
