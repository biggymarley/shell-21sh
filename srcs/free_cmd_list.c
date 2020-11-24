/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:18:31 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/24 22:51:05 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		del_red_lst(t_cmd **cmd)
{
	t_red	*ptr;

	while ((*cmd)->red)
	{
		free((*cmd)->red->file);
		(*cmd)->red->lfd = 0;
		(*cmd)->red->rfd = 0;
		(*cmd)->red->type = 0;
		ptr = (*cmd)->red;
		(*cmd)->red = (*cmd)->red->next;
		ft_memdel((void **)&ptr);
	}
	ft_memdel((void **)&(*cmd)->red);
}

void		del_cmd_lst(t_cmd **cmd)
{
	if ((*cmd))
	{
		if ((*cmd)->cmd)
			ft_strdel(&(*cmd)->cmd);
		if ((*cmd)->red)
			del_red_lst(cmd);
		if ((*cmd)->sep)
			del_cmd_lst(&(*cmd)->sep);
		if ((*cmd)->pipe)
			del_cmd_lst(&(*cmd)->pipe);
		ft_memdel((void **)cmd);
	}
}
