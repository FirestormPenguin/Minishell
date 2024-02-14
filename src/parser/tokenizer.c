/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:27:36 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/14 18:07:19 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void init_parser(t_parser *p, char *input)
{
	p->input_copy = ft_strdup(input);
	p->count = 0;
	ft_memset(p->tmp_token, '\0', sizeof(p->tmp_token));
	p->tokens = malloc((strlen(input) + 1) * sizeof(char *));
	p->i1 = 0;
	p->i2 = 0;
	p->i3 = 0;
	p->in_quote = 0;
	p->in_double_quote = 0;
    return;
}

void tokenize_parser(t_parser *p)
{
	while (p->input_copy[p->i1])
	{
		if (tokenize_single(p))
			break;
		if (tokenize_double(p))
			break;
		if (tokenize_quotes(p))
			break;
		if (tokenize_double_quotes(p))
			break;
		if (p->input_copy[p->i1] == '$' && p->input_copy[p->i1+1] != '$')
                base_expander(p);
        else
            p->tmp_token[p->i2++] = p->input_copy[p->i1++];
		if (p->input_copy[p->i1] == ' ' || p->input_copy[p->i1] == '\t'
			|| p->input_copy[p->i1] == '|' || p->input_copy[p->i1] == '>'
			|| p->input_copy[p->i1] == '<')
			break;
	}
}

char **tokenizer(char *input, int *token_count, t_parser *p)
{
	//t_parser	p;

	init_parser(p, input);

	while (p->input_copy[p->i1])
	{
		while (p->input_copy[p->i1] == ' ' || p->input_copy[p->i1] == '\t')
			p->i1++;
		p->i2 = 0;
		tokenize_parser(p);
		p->tmp_token[p->i2] = '\0';
		p->tokens[p->i3++] = ft_strdup(p->tmp_token);
		p->count++;
	}
	*token_count = p->count;
	p->tokens[p->count] = NULL;
	if (p->in_quote == 1)
	{
		printf("Error: unclosed quote\n");
		return (NULL);
	}
	return (p->tokens);
}
