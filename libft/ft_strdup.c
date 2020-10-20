/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 00:30:10 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 00:23:07 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		c;
	char	*d;

	if (!s)
		return (NULL);
	c = ft_strlen(s);
	if (!(d = (char *)malloc(sizeof(char) * (c + 1))))
		return (NULL);
	ft_memcpy(d, s, c);
	d[c++] = '\0';
	return (d);
}
