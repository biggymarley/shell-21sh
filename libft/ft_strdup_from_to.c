/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_from_to.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:12:10 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/24 05:00:15 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup_from_to(const char *s, int start, int end)
{
	int		c;
	char	*d;
	char	*rzlt;

	if (!s)
		return (NULL);
	c = 0;
	if (!(d = (char *)malloc(sizeof(char) * ((end - start) + 1))))
		return (NULL);
	while (start < end)
	{
		d[c++] = s[start++];
	}
	d[c] = '\0';
	rzlt = ft_strtrim(d);
	free(d);
	if (!rzlt[0])
		ft_strdel(&rzlt);
	return (rzlt);
}
