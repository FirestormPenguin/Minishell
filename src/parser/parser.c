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

t_tree	*build_tree(t_args *args, int pipe_count, int *i)
{
	t_tree	*tree;
	t_args	pipe_args;
	t_args	empty_args;
	int		count_pipe;

	pipe_args.str = "|";
	pipe_args.type = PIPE;
	empty_args.str = NULL;
	empty_args.type = EMPTY;
	if (*i == -1 && pipe_count > 0)
	{
		tree = create_node(&pipe_args);
		pipe_count--;
	}
	else if (*i == -1 && pipe_count <= 0)
		tree = create_node(&empty_args);
	else
		tree = create_node(&args[*i]);
	*i = *i + 1;
	printf ("\tNumber %d\n", *i);
	if (args[*i].type == DOUBLE_OUT || args[*i].type == HERE_DOC)	
		tree->right = build_tree(args, pipe_count, i);
	else if (args[*i].type == PIPE && count_pipe > 0)
		tree->right = build_tree(args, pipe_count, i);
	else if (args[*i].type == PIPE && count_pipe <= 0)
		*i = *i + 1;
	else if (args[*i].type == WORD || args[*i].type == IN_OUT)
		tree->left = build_tree(args, pipe_count, i);
	return (tree);
}

t_args	*fill_struct(char **mtx, int count)
{
	t_args	*tmp;
	int		i;

	i = -1;
	tmp = malloc((count) * sizeof(t_args));
	while (mtx[++i])
	{
		tmp[i].str = mtx[i];
		tmp[i].type = EMPTY;
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
			args[i].type = PIPE;
			tmp_pipe_count++;
		}
		else if (ft_strcmp(args[i].str, "<") == 0 || ft_strcmp(args[i].str, ">") == 0)
			args[i].type = IN_OUT;
		else if (ft_strcmp(args[i].str, ">>") == 0)
			args[i].type = DOUBLE_OUT;
		else if (ft_strcmp(args[i].str, "<<") == 0)
			args[i].type = HERE_DOC;
		else
			args[i].type = WORD;
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
	i = -1;
	root = build_tree(args, pipe_count, &i);
	printf("Attraversamento\n");
	inorderTraversal(root);
}
