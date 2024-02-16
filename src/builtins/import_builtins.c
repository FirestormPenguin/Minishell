/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mivendit <mivendit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:49:56 by mivendit          #+#    #+#             */
/*   Updated: 2024/02/15 10:49:56 by mivendit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	execute_env_command(t_list *list, t_process *proc)
{
	if (ft_strcmp(proc->args[0], "env") == 0 && (!proc->args[1]
			|| ft_strcmp(proc->args[1], "") == 0))
	{
		ft_env(proc->all->env);
		last_exit_code = 0;
		return (1);
	}
	else if (ft_strcmp(proc->args[0], "export") == 0)
	{
		ft_export(proc->args, proc->all);
		last_exit_code = 0;
		return (1);
	}
	else if (ft_strcmp(proc->args[0], "unset") == 0)
	{
		ft_unset_env(proc->args, proc->all);
		last_exit_code = 0;
		return (1);
	}
	return (0);
}

void	import_builtins(t_list *list, t_process *proc)
{
	int	result;

	if (ft_strcmp(proc->args[0], "exit") == 0)
	{
		ft_exit(proc->args);
	}
	else if (ft_strcmp(proc->args[0], "echo") == 0)
	{
		ft_echo(proc->args);
		last_exit_code = 0;
	}
	else if (ft_strcmp(proc->args[0], "pwd") == 0)
	{
		ft_pwd();
		last_exit_code = 0;
	}
	else if (ft_strcmp(proc->args[0], "cd") == 0)
	{
		result = ft_cd(proc->args, proc->all);
		last_exit_code = result;
	}
	else if (!execute_env_command(list, proc))
		list = forking(list, proc);
}
