/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 03:40:39 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/01 04:00:34 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int		ft_echo(char **str)
{
	int	i;
	int	j;
	int	s;

	i = 1;
	j = 0;
	if (ft_strcmp(str[0], "echo") == 0 ||
			ft_strcmp(str[0], "ECHO") == 0)
	{
		while (str[i])
		{
			ft_putstr(str[i]);
			if (str[i] && str[i + 1])
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}