/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 04:21:18 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/08 01:54:31 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int				if_exit(char **cmd)
{
	int			n;

	if (cmd && if_bult(cmd) == 1)
	{
		if ((n = ft_exit(cmd)) != -1337)
			return (n);
	}
	return (420);
}

void			free_red(t_red **red)
{
	t_red		*ptr;

	while ((*red))
	{
		if ((*red)->file)
			ft_strdel(&(*red)->file);
		(*red)->lfd = 0;
		(*red)->rfd = 0;
		(*red)->type = 0;
		ptr = (*red);
		(*red) = (*red)->next;
		ft_memdel((void **)&ptr);
	}
	ft_memdel((void **)&red);
}

void			free_cmd_list(t_cmd **cmd_line)
{
	ft_strdel(&(*cmd_line)->cmd);
	if ((*cmd_line)->red)
		free_red(&(*cmd_line)->red);
	if ((*cmd_line)->pipe)
		free_cmd_list(&(*cmd_line)->pipe);
	if ((*cmd_line)->sep)
		free_cmd_list(&(*cmd_line)->sep);
	ft_memdel((void **)cmd_line);
}
