/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 22:29:30 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 23:03:36 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	t_join join;

	join.i = 0;
	join.j = 0;
	join.a = 0;
	if (!s1 || !s2)
		return (0);
	join.a = ft_strlen(s1) + ft_strlen(s2);
	join.t = (char *)malloc(sizeof(char) * join.a + 1);
	if (join.t)
	{
		while (s1[join.i])
		{
			join.t[join.i] = s1[join.i];
			join.i++;
		}
		while (s2[join.j])
			join.t[join.i++] = s2[join.j++];
		join.t[join.i] = '\0';
		return (join.t);
	}
	free(join.t);
	return (0);
}
