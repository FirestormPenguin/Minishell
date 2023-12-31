/* ************************************************************************** */
/*                                      */
/*                            :::     ::::::::   */
/*   old_true_tokenizer.c                        :+:   :+:    :+:   */
/*                          +:+ +:+       +:+    */
/*   By: mirko <mirko@student.42.fr>                +#+  +:+       +#+    */
/*                        +#+#+#+#+#+   +#+     */
/*   Created: 2023/11/09 13:54:10 by codespace     #+#  #+#          */
/*   Updated: 2023/12/19 11:37:25 by mirko      ###   ########.fr    */
/*                                      */
/* ************************************************************************** */

#include "../../include/minishell.h"

#if 1
void init_var_tokenizer(char *input, char **input_copy, int *count, char ***tokens, int *i1, int *i3, bool *in_quote,bool *in_double_quote) {
    *input_copy = ft_strdup(input);
    *in_quote = false;
    *in_double_quote = false; 
    *count = 0;
    *tokens = malloc((strlen(input) + 1) * sizeof(char *));
    *i1 = 0;
    *i3 = 0;
}

#endif

char **tokenizer(char *input, int *token_count)
{
    char *input_copy;
    int count;
    char tmp_token[50];
    char **tokens;
    int i1;
    int i2;
    int i3;
    bool in_quote;
    bool in_double_quote;

    init_var_tokenizer(input, &input_copy, &count, &tokens, &i1, &i3, &in_quote, &in_double_quote);

    while (input_copy[i1])
    {
        while (input_copy[i1] == ' ' || input_copy[i1] == '\t')
            i1++;
        i2 = 0;
        while (input_copy[i1])
        {
            if (input_copy[i1] == ' ' || input_copy[i1] == '\t')
            {
                i1++;
                break;
            }
            else if (input_copy[i1] == '|')
            {
                tmp_token[i2] = '|';
                i2++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '>' && input_copy[i1 + 1] != '>')
            {
                tmp_token[i2] = '>';
                i2++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '<' && !input_copy[i1 + 1] == '<')
            {
                tmp_token[i2] = '<';
                i2++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '>' && input_copy[i1 + 1] == '>')
            {
                tmp_token[i2] = '>';
                tmp_token[i2 + 1] = '>';
                i2++;
                i2++;
                i1++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '<' && input_copy[i1 + 1] == '<')
            {
                tmp_token[i2] = '<';
                tmp_token[i2 + 1] = '<';
                i2++;
                i2++;
                i1++;
                i1++;
                break;
            }
            else if (input_copy[i1] == '\'' && !in_double_quote)
            {   
				in_quote = 1;
				i1++;
                while (input_copy[i1])
                {
					if (input_copy[i1] == '\'')
					{
						in_quote = 0;
						i1++;
						break;
					}
                    tmp_token[i2] = input_copy[i1];
                    i2++;
					i1++;
                }
				if (in_quote == 0)
					break;
            }
            else if (input_copy[i1] == '"' && !in_quote)
            {   
				in_double_quote = 1;
				i1++;
                while (input_copy[i1])
                {
					if (input_copy[i1] == '"')
					{
						in_double_quote = 0;
						i1++;
						break;
					}
                    tmp_token[i2] = input_copy[i1];
                    i2++;
					i1++;
                }
				if (in_double_quote == 0)
					break;
            }
            else
            {
                tmp_token[i2] = input_copy[i1];
				i2++;
                i1++;
                if (input_copy[i1] == ' ' || input_copy[i1] == '\t'
                    || input_copy[i1] == '|' || input_copy[i1] == '>'
                    || input_copy[i1] == '<')
                    break;
            }
        }
        tmp_token[i2] = '\0';
        tokens[i3] = ft_strdup(tmp_token);
        i3++;
        count++;
    }
    *token_count = count;
    tokens[count] = NULL;
	if (in_quote == 1)
	{
		printf("Error: unclosed quote\n");
		return (NULL);
	}
    return (tokens);
}

