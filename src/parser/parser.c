/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirko <mirko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:10 by codespace         #+#    #+#             */
/*   Updated: 2023/12/12 17:01:22 by mirko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_args	*fill_struct(char **mtx, int count)
{
	t_args	*tmp;
	int		i;

	i = -1;
	tmp = malloc((count) * sizeof(t_args));
	while (mtx[++i])
	{
		tmp[i].str = mtx[i];
		tmp[i].type = TOKEN_EMPTY;
	}
	return (tmp);
}

void check_type(t_args *args, int count, int *pipe_count)
{
	int i;
	int tmp_pipe_count;

	i = -1;
	tmp_pipe_count = 0;
	while (++i < count)
	{
		if (ft_strcmp(args[i].str, "|") == 0)
		{
			args[i].type = TOKEN_PIPE;
			tmp_pipe_count++;
		}
		else if (ft_strcmp(args[i].str, "<") == 0 || ft_strcmp(args[i].str, ">") == 0)
			args[i].type = TOKEN_REDIR;
		else if (ft_strcmp(args[i].str, ">>") == 0)
			args[i].type = TOKEN_DOUBLE_OUT;
		else if (ft_strcmp(args[i].str, "<<") == 0)
			args[i].type = TOKEN_HERE_DOC;
		else
			args[i].type = TOKEN_WORD;
	}
	*pipe_count = tmp_pipe_count;
}

void	tokenize_string(char *str)
{
	t_args	*args;
	t_tree	*root;
	char	**mtx;
	int		arg_count;
	int		pipe_count;
	int		i;

	mtx = tokenizer(str, &arg_count);
	i = 0;
	if (mtx == NULL)
		return ;
	args = fill_struct(mtx, arg_count);
	check_type(args, arg_count, &pipe_count);
	while (i < arg_count)
	{
		printf("str: %s\n", args[i].str);
		printf("type: %d\n", args[i].type);
		i++;
	}
	root = build_tree(args);
	printf("Attraversamento\n");
	inorderTraversal(root);
}
