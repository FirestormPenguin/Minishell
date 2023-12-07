/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spiacent <spiacent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:05 by codespace         #+#    #+#             */
/*   Updated: 2023/12/07 15:03:37 by spiacent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

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

/*generic utils*/
char	**ft_split(char const *s, char c);
int		count_split(char const *str, char c);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char*	ft_strtok(char* str, const char* delim);

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
char	**tokenizer(char *input, int *token_count, char *div);