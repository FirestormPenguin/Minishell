/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:27:44 by egiubell          #+#    #+#             */
/*   Updated: 2024/02/23 09:13:19 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_var_name(t_parser *p)
{
	char	*dollaro_start;
	int		len;
	char	*var;

	p->i1++;
	dollaro_start = &(p->input_copy[p->i1]);
	while (isalnum(p->input_copy[p->i1]) || p->input_copy[p->i1] == '_')
		p->i1++;
	len = &(p->input_copy[p->i1]) - dollaro_start;
	var = calloc(len + 1, sizeof(char *));
	strncpy(var, dollaro_start, len);
	var[len] = '\0';
	return (var);
}

void	question_expander(t_parser *p)
{
	int		i;
	char	*exit_code_str;

	if (g_last_exit_code != -1 || !g_last_exit_code)
	{
		exit_code_str = ft_itoa(g_last_exit_code);
		i = 0;
		while (i < ft_strlen(exit_code_str))
		{
			p->tmp_token[p->i2++] = exit_code_str[i];
			i++;
		}
		p->i1 += 2;
		free(exit_code_str);
	}
}
