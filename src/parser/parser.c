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

t_tree	*build_tree(char **mtx)
{
	t_tree *root = NULL;
	int i;

	i = 0;

	return (root);
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
		tmp[i].type = 0;
	}
	return (tmp);
}

void check_type(t_args *args, int count)
{
	int i;

	i = -1;
	while (++i < count)
	{
		if (ft_strcmp(args[i].str, "|") == 0)
			args[i].type = 1;
		else if (ft_strcmp(args[i].str, "<") == 0 || ft_strcmp(args[i].str, ">") == 0)
			args[i].type = 2;
		else if (ft_strcmp(args[i].str, "<<") == 0 || ft_strcmp(args[i].str, ">>") == 0)
			args[i].type = 3;
		else
			args[i].type = 0;
	}
	//printf("type: %d\n", args[i].type);
}

void	tokenize_string(char *str)
{
	t_args	*args;
	char	**mtx;
	int		arg_count;
	t_tree	*tree;

	mtx = tokenizer(str, &arg_count);
	int i = 0;
	if (mtx == NULL)
		return ;
	args = fill_struct(mtx, arg_count);
	check_type(args, arg_count);
	
	while (i < arg_count)
	{
		printf("str: %s\n", args[i].str);
		printf("type: %d\n", args[i].type);
		i++;
	}
	//tree = build_tree(args);
	//inorderTraversal(tree);
}
