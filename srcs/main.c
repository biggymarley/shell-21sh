/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:25:56 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/08 03:17:55 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void			func(int signal)
{
	ft_putstr("\n\033[1;91mbiggyshell{v.200}$>\033[1;96m ");
}

void			alias(t_cmd *cmd)
{
	alias_checker(&cmd->cmd);
	if (cmd->pipe)
		alias(cmd->pipe);
	if (cmd->sep)
		alias(cmd->sep);
}

int				read_parse(t_core *core)
{
	ft_putstr("\033[1;91mbiggyshell{v.200}$>\033[1;96m ");
	get_next_line(0, &(*core).buff);
	if ((*core).buff && (*core).buff[0] && (*core).buff[0] == '\n')
	{
		ft_strdel(&(*core).buff);
		return (0);
	}
	if (((*core).cmd_line = parser(&(*core).buff)) == NULL)
	{
		ft_strdel(&(*core).buff);
		del_cmd_lst(&(*core).cmd_line);
		return (0);
	}
	return (1);
}

int				core(t_env **env)
{
	t_core		core;
	int			n;

	core.buff = NULL;
	core.str = NULL;
	signal(SIGINT, func);
	while (1)
	{
		if (!(read_parse(&core)))
			continue ;
		alias(core.cmd_line);
		if ((n = execute_cmd(core.cmd_line, env, 0)) != 666 && n != 555)
			break ;
		del_cmd_lst(&core.cmd_line);
		ft_strdel(&core.buff);
	}
	del_cmd_lst(&core.cmd_line);
	ft_strdel(&core.buff);
	return (n);
}

int				main(int ac, char **av, char **environ)
{
	t_env		*env;
	int			n;
	t_cmd		*cmd_line;

	env = NULL;
	env_to_list(&env, environ);
	n = core(&env);
	free_env(&env, del);
	return (n);
}
