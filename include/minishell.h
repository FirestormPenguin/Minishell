/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:05 by codespace         #+#    #+#             */
/*   Updated: 2024/03/20 10:03:30 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

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
# include <signal.h>

# define MINISHELL_H

extern int	g_last_exit_code;

/*Utility Macro*/
# define WORD 0
# define PIPE 1
# define IN 2
# define OUT 3
# define DOUBLE_OUT 4
# define HERE_DOC 5
# define SET_ACTUAL 10
# define GET_ARGS 11
# define GET_LIST 12
# define GET_PARSER 13
# define GET_ENV 14

/*Exit Macro*/
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

/*Struct*/
typedef struct s_list
{
	char			**mtx;
	int				type;
	struct s_list	*next;
}	t_list;

struct		s_parser;

typedef struct s_env4mini
{
	char			**env;
	struct s_parser	*pars;
}	t_env4mini;

typedef struct s_parser
{
	char		*input_copy;
	int			count;
	char		tmp_token[50000];
	char		**tokens;
	int			i1;
	int			i2;
	int			i3;
	int			in_quote;
	int			in_double_quote;
	t_env4mini	*cp_env;
}	t_parser;

typedef struct s_process
{
	pid_t		pid;
	int			status;
	char		*path;
	char		**args;
	int			saved_stdin;
	int			saved_stdout;
	int			pipe_fd[2];
	int			saved_fd;
	int			red_ctrl;
	t_env4mini	*all;
}	t_process;

typedef struct s_grb_collector
{
	t_list		*list_ptr;
	t_env4mini	*env_ptr;
	t_parser	*parser_ptr;
	t_process	*proc_ptr;
}	t_grb_collector;

/*Main*/
void			get_input(t_env4mini *all, t_parser *pars);

/*Utils*/
// void			*struct_box(t_struct_pointers *ptr_struct, int operation);
//void			free_args(t_args *args);
void			free_list(t_list *list);
void			free_parser(t_parser *parser);
void			free_env4mini(t_env4mini *env);
void			free_all_generic(char *path, char **args);
void			free_double_pointer(char **ptr);
void			free_exit(int exit_code, t_grb_collector *grb_ptr);

/*Parser*/
t_list			*parser(char *str, t_parser *pars);
t_list			*init_list(char **mtx);
t_list			*ft_lstnew(void);

/*Parser Utils*/
int				check_type(char *str);
void			scroll_list(t_list *node);

/*Parser_list_utils*/
void			init_first_node(t_list **list, char **mtx, int *i,
					int *next_type);
t_list			*create_node(char **mtx, int *i, int *next_type);
t_list			*ft_lstnew(void);

/*Tokenizer*/
char			**tokenizer(char *input, int *token_count, t_parser *pars);

/*Tokenizer Utils*/
int				tokenize_single(t_parser *p);
int				tokenize_double(t_parser *p);
int				tokenize_quotes(t_parser *p);
int				tokenize_double_quotes(t_parser *p);
void			base_expander(t_parser *p);
char			*get_var_name(t_parser *p);
void			question_expander(t_parser *p);

/*Exe*/
void			exe(t_list *list, t_env4mini *all);
void			forking(t_list *list, t_process *proc,
					t_list *tmp_list, int pipe_count);

/*Exe Utils*/
int				check_error_redirection(t_list *list);
int				setup_redirection(t_list *list);
void			init_vars(t_process *proc, int *i);
t_list			*fill_args(t_list *list, t_process *proc, int i);
char			*path_finder(char **cmd, t_env4mini *all);
char			*ft_getenv(char *name, char **env);
t_grb_collector	*set_garbage_collector(t_list *list, t_process *proc);

/*Redirections*/
void			input(char *str);
void			output(char *str);
void			append(char *str);
void			here_doc(char *str);

/*Redirections_utils*/
int				redirections(t_list *list);
void			write_into_fd(char *str);

/*Check redirection*/
int				check_error_redirection(t_list *list);

/*Enviromenrt*/
int				copy_env(char **env, t_env4mini *all);
void			print_env_copy(t_env4mini *all);
void			free_env(t_env4mini *all);
void			increment_shlvl(t_env4mini *all);

/*Built-in Func*/
int				ft_echo(char **command_string);
void			ft_exit(char **args, t_grb_collector *grb_ptr);
int				ft_pwd(void);
int				ft_env(char **env);
int				ft_cd(char **args, t_env4mini *all);
void			ft_export(char **args, t_env4mini *all);
void			ft_unset(char **args, t_env4mini *all);

/*Utils Built-in*/
void			ft_setenv(char *name, char *value, t_env4mini *all);
int				import_builtins(t_process *proc, t_grb_collector *grb_ptr);
int				find_valid_equals(char *str);
int				check_builtins(t_process *proc);
int				check_env_command(t_process *proc);
int				execute_env_command(t_process *proc);
int				is_valid_str(char *str);
int				is_valid_val(char *str);

/*Signal*/
void			sigquit_handle(int sig);
void			sigint_handle(int sig);
void			sigquit_handle_child(int sig);
void			sigint_handle_child(int sig);

#endif
