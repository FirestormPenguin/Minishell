/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:05 by codespace         #+#    #+#             */
/*   Updated: 2024/02/12 03:51:06 by mivendit         ###   ########.fr       */
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
# include <fcntl.h>
# include <limits.h>

/*Utility Macro*/
#define WORD 0
#define PIPE 1
#define IN 2
#define OUT 3
#define DOUBLE_OUT 4
#define HERE_DOC 5
#define SET_ACTUAL 10
#define GET_ARGS 11
#define GET_LIST 12
#define GET_PARSER 13
#define GET_ENV 14

/*Exit Macro*/
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

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

typedef	struct	s_env4mini
{
	char	**env;
}	t_env4mini;

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
	t_env4mini *cp_env;
}	t_parser;


typedef struct s_process
{
    pid_t       pid;
    int         status;
    char        *path;
    char        **args;
    int         saved_stdin;
    int         saved_stdout;
    t_env4mini  *all;
}               t_process;



typedef	struct	s_struct_pointers
{
	t_args		*args_ptr;
    t_list		*list_ptr;
    t_parser	*parser_ptr;
    t_env4mini	*env_ptr;
}	t_struct_pointers;

/*Main*/
void getInput(t_env4mini *all, t_parser *pars);

/*Utils*/
void	*struct_box(t_struct_pointers *ptr_struct, int operation);
void	free_all_generic(char *path, char **args);
void 	free_exit(int exit_code);

/*Parser*/
t_list	*parser(char *str, t_parser *pars);
t_list	*init_list(char **mtx);
static t_list	*ft_lstnew();

/*Parser Utils*/
int		check_type(char *str);
void	scroll_list(t_list *node);

/*Tokenizer*/
char	**tokenizer(char *input, int *token_count, t_parser *pars);

/*Tokenizer Utils*/
int		tokenize_single(t_parser *p);
int		tokenize_double(t_parser *p);
int		tokenize_quotes(t_parser *p);
int		tokenize_double_quotes(t_parser *p);

/*Exe*/
void	exe(t_list *list, t_env4mini *all);
t_list	*forking(t_list *list, t_process *proc);

/*Exe Utils*/
int		check_error_redirection(t_list *list);
int		setup_redirection(t_list *list, t_process *proc);
void	init_vars(t_process *proc, int *i, t_env4mini *all);
char	**fill_args(t_list *list, char **args, int i);
int		check_mtx(t_list *list, t_process *proc, int i);
void	reset_stdin_stdout(t_process *proc);

/*Redirections*/
void	redirections(t_list *list, t_process *proc);

/*Redirections_utils*/
void write_into_fd(char *str);

/*Enviromenrt*/
int		copy_env(char **env, t_env4mini *all);
void	print_env_copy(t_env4mini *all);
void	free_env(t_env4mini *all);

/*Built-in Func*/
int		ft_echo(char **command_string);
void	ft_exit(char **args);
int		ft_pwd(void);
int		ft_env(char **env);
int		ft_cd (char **args, t_env4mini *all);
void	ft_export(char **args, t_env4mini *all);

char	*path_finder(char **cmd, t_env4mini *all);
char	*ft_getenv(char *name, char **env);
void 	base_expander(t_parser *p);
#endif
