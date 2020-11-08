/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putalnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 04:48:50 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 04:49:01 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putalnum_fd(char const *str, int fd)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				break ;
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
}
