/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:42:09 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 02:14:59 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		pipe_reader(char **str)
{
	char	*buff;
	char	*ptr;

	buff = NULL;
	while (1)
	{
		ft_putstr("pipe>");
		get_next_line(0, &buff);
		if (buff[0] != '\n')
			break ;
		ft_strclr(buff);
	}
	ptr = buff;
	buff = ft_strtrim(buff);
	free(ptr);
	ptr = (*str);
	(*str) = ft_strjoin((*str), buff);
	free(ptr);
}
