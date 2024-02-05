/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:05 by codespace         #+#    #+#             */
/*   Updated: 2024/02/01 17:18:13 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
#include <fcntl.h>

/*Utility Macro*/
#define WORD 0
#define PIPE 1
#define IN 2
#define OUT 3
#define DOUBLE_OUT 4
#define HERE_DOC 5

/*Struct*/
typedef struct s_args
{
	char	*str;
	int		type;
}		t_args;

typedef struct s_list
{
	char			**mtx;
	int				type;
	struct s_list	*next;
}		t_list;

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

typedef	struct	s_env4mini
{
	char	**env;
}	t_env4mini;

/*tokenizer utils*/
int		tokenize_single(t_parser *p);
int		tokenize_double(t_parser *p);
int		tokenize_quotes(t_parser *p);
int		tokenize_double_quotes(t_parser *p);

/*parser*/
t_list	*tokenize_string(char *str);
t_args	*fill_struct(char **mtx, int count);
int		check_type(char *str);
void	scroll_list(t_list *node);

/*tokenizer*/
char	**tokenizer(char *input, int *token_count);

/*redirections*/
void	redirections(t_list *list);

/*Enviromenrt*/
int		copy_env(char **env, t_env4mini *all);
void	print_env_copy(t_env4mini *all);
#endif
