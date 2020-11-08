/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:31:28 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 00:40:37 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int				clean(t_alias *alias, char **line)
{
	if ((*alias).file)
	{
		(*alias).cmd = ft_strsplit((*alias).file, '=');
		if ((*alias).cmd && (*alias).cmd[0] &&
			!(ft_strcmp((*alias).cc[0], (*alias).cmd[0])) && (*alias).cmd[1])
		{
			while ((*alias).i)
			{
				ft_move_replace((*line));
				(*alias).i--;
			}
			(*alias).tmp = (*line);
			(*line) = ft_strjoin((*alias).cmd[1], (*line));
			free((*alias).tmp);
			ft_strdel(&(*alias).file);
			delkill((*alias).cmd);
			delkill((*alias).cc);
			close((*alias).f);
			return (-1);
		}
		delkill((*alias).cmd);
	}
	return (0);
}

int				alias_checker(char **line)
{
	t_alias		alias;

	alias.f = open(".biggyrc", O_RDONLY);
	alias.cmd = NULL;
	alias.cc = ft_strsplit((*line), ' ');
	alias.i = ft_strlen(alias.cc[0]);
	while (get_next_line(alias.f, &alias.file) > 0)
	{
		alias.tmp = alias.file;
		alias.file = ft_strtrim(alias.file);
		free(alias.tmp);
		if (clean(&alias, line) < 0)
			return (-1);
		ft_strdel(&alias.file);
	}
	close(alias.f);
	delkill(alias.cc);
	return (1);
}

int				read_alias_file(t_alias2 *alias, char **line)
{
	while (get_next_line((*alias).f, &(*alias).file) > 0)
	{
		(*alias).tmp = (*alias).file;
		(*alias).file = ft_strtrim((*alias).file);
		free((*alias).tmp);
		if ((*alias).file)
		{
			(*alias).cmd = ft_strsplit((*alias).file, '=');
			if ((*alias).cmd && (*alias).cmd[0] &&
				!(ft_strcmp((*alias).cc[0], (*alias).cmd[0])))
			{
				ft_putendl_fd("alias already exist try an other", 2);
				delkill((*alias).cmd);
				return (-1);
			}
			delkill((*alias).cmd);
		}
		ft_strdel(&(*alias).file);
	}
	return (0);
}

int				alias_check(char **line)
{
	t_alias2	alias;

	alias.f = open(".biggyrc", O_RDONLY);
	alias.cmd = NULL;
	alias.cc = ft_strsplit((*line), '=');
	if (!alias.cc[1])
	{
		ft_putendl_fd("alias : format error", 2);
		return (-1);
	}
	if (read_alias_file(&alias, line) < 0)
		return (-1);
	close(alias.f);
	delkill(alias.cc);
	return (1);
}

void			write_file(t_alias3 *alias, char **line)
{
	(*alias).f = open(".biggyrc", O_RDONLY, 0644);
	while (get_next_line((*alias).f, &(*alias).file) > 0)
	{
		(*alias).tmp = (*alias).file;
		(*alias).file = ft_strtrim((*alias).file);
		free((*alias).tmp);
		if ((*alias).file && (*alias).file[0] && (*alias).file[0] != '#')
			ft_putendl((*alias).file);
		ft_strdel(&(*alias).file);
	}
}
