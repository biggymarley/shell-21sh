/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:25:56 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/04 02:42:44 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"


char		*g_ine = NULL;

void			func(int signal)
{
	// ft_putstr("\n\033[1;ss{v.200}$>\033[1;96m ");
	// int		fd;

	// fd = open("/dev/ttys005", O_RDWR);
	// ft_putchar_fd('\n', 0);
	// read_parse(core);
	// close(fd);
	int		i;
	i = 0;
}

void			alias(t_cmd *cmd)
{
	if (cmd->cmd)
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
	// (*core).buff = ft_readline();
	if((*core).buff == NULL)
	{
		ft_strdel(&(*core).buff);
		return (420);
	}
	if (((*core).buff && (*core).buff[0] && (*core).buff[0] == '\n'))
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
	signal(SIGINT, func);
	while (1)
	{
		if (!(n = (read_parse(&core))))
			continue ;
		if(n == 420)
		{
			ft_putendl_fd("exit", 2);
			break;
		}
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
	t_env			*env;
	int				n;
	t_cmd			*cmd_line;
	struct termios	backup;

	env = NULL;
	env_to_list(&env, environ);
	// backup = ft_setterm();
	n = core(&env);
	// tcsetattr(STDIN_FILENO, TCSANOW, &backup);
	free_env(&env, del);
	return (n);
}
