/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiubell <egiubell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:18:40 by mivendit          #+#    #+#             */
/*   Updated: 2024/04/24 13:51:26 by egiubell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handle(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_last_exit_code = 130;
}

void	sigquit_handle(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_last_exit_code = 131;
}

void	sigint_handle_child(int sig)
{
	(void)sig;
	printf("\n");
	g_last_exit_code = 130;
}

void	sigquit_handle_child(int sig)
{
	(void)sig;
	printf("\n");
	g_last_exit_code = 131;
}
