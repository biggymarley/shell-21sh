/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:15:52 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 01:16:54 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

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
