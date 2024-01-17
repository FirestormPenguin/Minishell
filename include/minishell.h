/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:05 by codespace         #+#    #+#             */
/*   Updated: 2024/01/17 16:04:54 by egiubell         ###   ########.fr       */
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
#define TOKEN_EMPTY 0
#define TOKEN_WORD 1
#define TOKEN_PIPE 2
#define TOKEN_REDIR 3
#define TOKEN_DOUBLE_OUT 4
#define TOKEN_HERE_DOC 5

typedef struct s_args
{
	char	*str;
	int		type;
}		t_args;

typedef struct s_tree
{
	char			*data;
	int				type;
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*prev;
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

/*tokenizer utils*/
int tokenize_single(t_parser *p);
int tokenize_double(t_parser *p);
int tokenize_quotes(t_parser *p);
int tokenize_double_quotes(t_parser *p);

/*tree utils*/
t_tree	*create_node(char *str, int type, t_tree *prevNode, t_tree *rootNode);
void	inorderTraversal(t_tree *root);

/*parser*/
void	tokenize_string(char *str);
t_args	*fill_struct(char **mtx, int count);

/*build tree*/
t_tree	*build_tree(t_args *args, int pipe_count);

/*tokenizer*/
char	**tokenizer(char *input, int *token_count);

#endif