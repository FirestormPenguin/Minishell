/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirko <mirko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:05 by codespace         #+#    #+#             */
/*   Updated: 2023/12/20 23:16:47 by mirko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/include/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

/*Utility Macro*/
#define MAX_TOKEN_LENGTH 50
#define EMPTY 0
#define WORD 1
#define PIPE 2
#define IN_OUT 3
#define DOUBLE_OUT 4
#define HERE_DOC 5

typedef struct s_args
{
	char	*str;
	int		type;
}		t_args;

typedef struct s_tree
{
	t_args			*data;
	struct s_tree	*left;
	struct s_tree	*right;
}		t_tree;

typedef struct s_parser
{
	char *input_copy;
	int count;
	char tmp_token[50000];
	char **tokens;
	int i1;
	int i2;
	int i3;
	int in_quote;
	int in_double_quote;
}	t_parser;

/*generic utils*/
// char	**ft_split(char const *s, char c);
int		count_split(char const *str, char c);
// char	*ft_strdup(const char *s1);
// char	*ft_strchr(const char *s, int c);
// int		ft_strcmp(const char *s1, const char *s2);
// char	*ft_strtok(char* str, const char* delim);

/*tree utils*/
t_tree	*create_node(t_args *args);
t_tree*	insertLeft(t_tree* root, t_args *args);
t_tree*	insertRight(t_tree* root, t_args *args);
void	inorderTraversal(t_tree *root);

/*parser*/
void	tokenize_string(char *str);
t_args	*fill_struct(char **mtx, int count);
t_tree	*build_tree(char **mtx);

/*tokenizer*/
char	**tokenizer(char *input, int *token_count);

#endif