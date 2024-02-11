/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:27:44 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/12 03:36:20 by mivendit         ###   ########.fr       */
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
    char *input_expanded;

    input_expanded = calloc(50, sizeof(char *));
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
                //printf("input cpy : %s\n", p->input_copy);
                char *var_value = ft_getenv(var, p->cp_env->env);
                if (var_value != NULL)
				{
					int i = 0;
					while(i < strlen(var_value))
                    {
                        p->tmp_token[p->i2++] = var_value[i];
						i++;
                    }
                }
                free(var);
            }
            else
            {
                p->tmp_token[p->i2++] = p->input_copy[p->i1++];
            }
        }
        if (p->in_double_quote == 0)
            return (1);
    }
    return (0);
}
