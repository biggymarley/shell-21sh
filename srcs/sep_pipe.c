/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 03:43:10 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 03:43:29 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int				pipe_parser(t_cmd **cmd_list, char **cmd, int i)
{
	if ((*cmd_list)->cmd == NULL)
	{
		errors(0, cmd_list);
		return (0);
	}
	(*cmd_list)->pipe = (t_cmd *)ft_memalloc(sizeof(t_cmd));
	(*cmd_list) = (*cmd_list)->pipe;
	if (!(*cmd)[i + 1] && i > 0)
		pipe_reader(cmd);
	return (1);
}

int				sep_parser(t_cmd **cmd_list, char *cmd, int i, t_cmd **last_sep)
{
	if ((*cmd_list)->cmd == NULL)
	{
		errors(0, cmd_list);
		return (0);
	}
	if ((*last_sep) != NULL)
		(*cmd_list) = (*last_sep);
	(*cmd_list)->sep = (t_cmd *)ft_memalloc(sizeof(t_cmd));
	(*last_sep) = (*cmd_list)->sep;
	(*cmd_list) = (*cmd_list)->sep;
	return (1);
}
