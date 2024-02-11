/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:27:44 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/11 11:42:05 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int tokenize_single(t_parser *p)
{
	if (p->input_copy[p->i1] == '|')
	{
		p->tmp_token[p->i2++] = '|';
		p->i1++;
		return (1);
	}
	if (p->input_copy[p->i1] == '>' && p->input_copy[p->i1 + 1] != '>')
	{
		p->tmp_token[p->i2++] = '>';
		p->i1++;
		return (1);
	}
	if (p->input_copy[p->i1] == '<' && p->input_copy[p->i1 + 1] != '<')
	{
		p->tmp_token[p->i2++] = '<';
		p->i1++;
		return (1);
	}
	return (0);
}

int tokenize_double(t_parser *p)
{
	if (p->input_copy[p->i1] == '>' && p->input_copy[p->i1 + 1] == '>')
	{
		p->tmp_token[p->i2] = '>';
		p->tmp_token[p->i2 + 1] = '>';
		p->i2 += 2;
		p->i1 += 2;
		return (1);
	}
	if (p->input_copy[p->i1] == '<' && p->input_copy[p->i1 + 1] == '<')
	{
		p->tmp_token[p->i2] = '<';
		p->tmp_token[p->i2 + 1] = '<';
		p->i2 += 2;
		p->i1 += 2;
		return (1);
	}
	return (0);
}

int tokenize_quotes(t_parser *p)
{
	if (p->input_copy[p->i1] == '\'' && !p->in_double_quote)
	{
		p->in_quote = 1;
		p->i1++;
		while (p->input_copy[p->i1])
		{
			if (p->input_copy[p->i1] == '\'')
			{
				p->in_quote = 0;
				p->i1++;
				return (1);
			}
			p->tmp_token[p->i2++] = p->input_copy[p->i1++];
		}
		if (p->in_quote == 0)
			return (1);
	}
	return (0);
}

char *get_var_name(t_parser *p)
{
	p->i1++;
	char *dollaro_start = &(p->input_copy[p->i1]);
	while (isalnum(p->input_copy[p->i1]) || p->input_copy[p->i1] == '_')
		p->i1++;
	int len = &(p->input_copy[p->i1]) - dollaro_start;
	char *var = calloc(len + 1, sizeof(char *));
	strncpy(var, dollaro_start, len);
	//printf("%s\n", var);
	var[len]='\0';
	return (var);
}

int tokenize_double_quotes(t_parser *p)
{
	char *var;
	char *var_content;

	var_content = calloc(50, sizeof(char *));
	if (p->input_copy[p->i1] == '"' && !p->in_quote)
	{
		p->in_double_quote = 1;
		p->i1++;
		while (p->input_copy[p->i1])
		{
			if (p->input_copy[p->i1] == '"')
			{
				p->in_double_quote = 0;
				p->i1++;
				return (1);
			}
			if (p->input_copy[p->i1] == '$')
			{
				var = get_var_name(p);
				var_content = ft_getenv(var, p->cp_env->env);
				printf("%s\n", var_content);
				//var_content = ft_getenv(var, p->cp_env->env);
				return (1);
			}
			p->tmp_token[p->i2++] = p->input_copy[p->i1++];
		}
		if (p->in_double_quote == 0)
			return (1);
	}
	return (0);
}

