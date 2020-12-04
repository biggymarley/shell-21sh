/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 00:49:40 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/01 05:21:14 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		tabs_skipper(char *buff)
{
	int		i;
	int		len;

	i = 0;
	while (buff[i] && buff[i] == '\t')
		ft_move_replace(&buff[i]);
}

void		replace(t_red *red)
{
	char	*ptr;

	if (red->file[0])
	{
		ptr = ft_strrchr(red->file, '\n');
		*ptr = '\0';
	}
}

void		read_herdoc(t_red *red)
{
	char	buff[1000];
	char	*ptr;
	char	*key;

	key = ft_strdup(red->file);
	ft_strclr(red->file);
	ft_bzero(buff, 1000);
	while (1)
	{
		ft_putstr("$-herdoc> ");
		if (!(read(0, buff, 1000)))
			break ;
		if (buff[0] != '\n' && !ft_strncmp(buff, key, (ft_strlen(buff) - 1)))
			break ;
		if ((red->type & HERDOC) && (red->type & CLOSE_RFD))
			tabs_skipper(buff);
		ptr = red->file;
		red->file = ft_strjoin(red->file, buff);
		free(ptr);
		ft_bzero(buff, 1000);
	}
	replace(red);
	free(key);
}
