/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:15:52 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/13 22:17:23 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int				if_slash_or_dot(char *str)
{
	if (str)
		if (str[0] == '/' ||
			(str[0] == '.' && str[1] == '/'))
			if (access(str, F_OK) == -1)
			{
				ft_putstr(str);
				ft_putendl_fd(" : no such file or directory.", 2);
				return (-1);
			}
	return (0);
}

int				filter(char **line, t_env *env)
{
	if (if_home(line, env) < 0)
	{
		delkill(line);
		return (0);
	}
	if (!(ft_check_dollars(line, env)))
	{
		delkill(line);
		return (0);
	}
	if (if_slash_or_dot(line[0]) == -1)
	{
		delkill(line);
		return (0);
	}
	return (1);
}

char			**cmd_finder(t_env *env, char *cmd)
{
	char		**line;
	char		*ptr;
	char		**tmp;

	if (cmd)
	{
		ptr = ft_strtrim(cmd);
		if (ptr[0] == '\0')
		{
			ft_strdel(&ptr);
			return (NULL);
		}
		line = ft_strsplit(ptr, ' ');
		rebase_all(line);
		if (!filter(line, env))
		{
			ft_strdel(&ptr);
			return (NULL);
		}
		if (!if_bult(line))
			line = found_func(env, line[0], line);
		ft_strdel(&ptr);
	}
	return (line);
}

int				fdhandler(int cmd_nbr, int fd_handler, int *fd, t_cmd *cmd_list)
{
	if (cmd_nbr != 0)
		dup2(fd_handler, 0);
	if (cmd_list->pipe)
		dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	if (fd_handler != 0)
		close(fd_handler);
	if (cmd_list->red)
		if (!red_duper(cmd_list->red))
			return (0);
	return (1);
}
