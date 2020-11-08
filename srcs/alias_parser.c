/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 00:39:20 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 00:40:47 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void			alias_parser(char **line)
{
	t_alias3 alias;

	alias.i = 1;
	alias.file = NULL;
	if (counter(line) > 2)
	{
		ft_putendl_fd("alias : too many arguments", 2);
		return ;
	}
	if (!line[alias.i])
		write_file(&alias, line);
	else
	{
		alias.f = open(".biggyrc", O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((alias_check(&line[alias.i])) > 0)
			ft_putendl_fd(line[alias.i], alias.f);
	}
	if (alias.f != 0)
		close(alias.f);
}
