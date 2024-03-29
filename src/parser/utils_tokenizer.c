/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:27:44 by egiubell          #+#    #+#             */
/*   Updated: 2024/03/08 21:48:51 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tokenize_single(t_parser *p)
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

int	tokenize_double(t_parser *p)
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

int	tokenize_quotes(t_parser *p)
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

int	tokenize_double_quotes(t_parser *p)
{
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
			if (p->input_copy[p->i1] == '$' && p->input_copy[p->i1 + 1] != '$')
			{
				base_expander(p);
				return (1);
			}
			else
				p->tmp_token[p->i2++] = p->input_copy[p->i1++];
		}
		if (p->in_double_quote == 0)
			return (1);
	}
	return (0);
}

void	base_expander(t_parser *p)
{
	char	*var;
	char	*var_value;
	int		i;

	if (p->input_copy[p->i1 + 1] == '?')
		question_expander(p);
	else
	{
		var = get_var_name(p);
		var_value = ft_getenv(var, p->cp_env->env);
		if (var_value != NULL)
		{
			i = 0;
			while ((size_t)i < strlen(var_value))
			{
				p->tmp_token[p->i2++] = var_value[i];
				i++;
			}
		}
		if (var != NULL)
			free(var);
	}
}
