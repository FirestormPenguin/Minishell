/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:05 by codespace         #+#    #+#             */
/*   Updated: 2024/02/05 17:12:47 by egiubell         ###   ########.fr       */
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

/*main*/
void getInput(t_env4mini *all);

/*utils*/
void	free_all(char *path, char **args);

/*parser*/
t_list	*parser(char *str);
t_list	*init_list(char **mtx);
static t_list	*ft_lstnew();

/*parser utils*/
int		check_type(char *str);
void	scroll_list(t_list *node);

/*tokenizer*/
char	**tokenizer(char *input, int *token_count);

/*tokenizer utils*/
int		tokenize_single(t_parser *p);
int		tokenize_double(t_parser *p);
int		tokenize_quotes(t_parser *p);
int		tokenize_double_quotes(t_parser *p);

/*exe*/
void	exe(t_list *list, t_env4mini *all);
t_list	*forking(t_list *list, pid_t pid, int status, char *path, char **args, int saved_stdin, int saved_stdout, t_env4mini *all);

/*exe utils*/
int		check_error_redirection(t_list *list);
int		setup_redirection(t_list *list);
void	init_vars(char **path, char ***args, int *i);
char	**fill_args(t_list *list, char **args, int i);
int		check_mtx(t_list *list, char *path, char **args, int i);

/*redirections*/
void	redirections(t_list *list);

/*Enviromenrt*/
int		copy_env(char **env, t_env4mini *all);
void	print_env_copy(t_env4mini *all);
void	free_env(t_env4mini *all);

#endif
