/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 23:10:24 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/24 22:58:06 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int				c(t_dupexe *dupexe, char **cmd, t_env **env, t_cmd *cmd_list)
{
	(*dupexe).nev = NULL;
	if (!cmd && !cmd_list && !env)
		return (1);
	if (((*dupexe).built_cmd = if_bult(cmd)))
		execve_built(cmd[0], cmd, env, (*dupexe).built_cmd);
	(*dupexe).nev = ltot((*env));
	return (0);
}

void			execute_all(t_dupexe *dupexe, char **cmd, t_env **env)
{
	if (!(*dupexe).built_cmd)
	{
		execve(cmd[0], cmd, (*dupexe).nev);
		if (access(cmd[0], F_OK) != 0)
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": no such file or directory.\n", 2);
		}
		else
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": permision denied\n", 2);
		}
	}
	else if ((*dupexe).built_cmd)
		execve_child(cmd[0], cmd, env, (*dupexe).built_cmd);
	exit(EXIT_FAILURE);
}

int				dupexe(char **cmd, t_env **env, int cmd_nbr, t_cmd *cmd_list)
{
	static int	fd_handler;
	t_dupexe	dupexe;

	if (c(&dupexe, cmd, env, cmd_list))
	{
		close(fd_handler);
		return (1);
	}
	if (pipe(dupexe.fd) == -1)
	{
		delkill(dupexe.nev);
		return (0);
	}
	else if (!fork())
	{
		if (!(fdhandler(cmd_nbr, fd_handler, dupexe.fd, cmd_list)))
			exit(EXIT_FAILURE);
		execute_all(&dupexe, cmd, env);
	}
	delkill(dupexe.nev);
	close(dupexe.fd[1]);
	if (cmd_nbr != 0)
		close(fd_handler);
	fd_handler = dupexe.fd[0];
	return (1);
}

int				fillter(char ***cmd, t_cmd *cmd_list, t_env **env)
{
	if (cmd_list->cmd == NULL)
		return (0);
	if (if_slash_or_dot(cmd_list->cmd) == -1)
		return (0);
	if (!((*cmd) = cmd_finder((*env), cmd_list->cmd)) && !cmd_list->red)
	{
		delkill((*cmd));
		return (0);
	}
	if ((*cmd) && !(*cmd)[0] && !cmd_list->red)
	{
		delkill((*cmd));
		return (0);
	}
	return (1);
}

int				execute_cmd(t_cmd *cmd_list, t_env **env, int cmd_nbr)
{
	char		**cmd;
	int			n;

	cmd = NULL;
	if (!fillter(&cmd, cmd_list, env))
		return (555);
	if ((n = if_exit(cmd)) != 420)
	{
		delkill(cmd);
		return (n);
	}
	dupexe(cmd, env, cmd_nbr, cmd_list);
	delkill(cmd);
	if (cmd_list->pipe)
		execute_cmd(cmd_list->pipe, env, cmd_nbr + 1);
	else
	{
		dupexe(NULL, 0, 0, 0);
		while (wait(NULL) > 0)
		{
		}
	}
	if (cmd_list->sep)
		execute_cmd(cmd_list->sep, env, 0);
	return (666);
}
