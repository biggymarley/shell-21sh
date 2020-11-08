/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cremplire.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 20:28:53 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 22:25:45 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_cremplire(char *r, char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != c)
	{
		r[j] = s[i];
		i++;
		j++;
	}
	r[j] = '\0';
}

void		ft_whiteremplire(char *r, char const *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] && s[i] > 32)
	{
		r[j] = s[i];
		i++;
		j++;
	}
	r[j] = '\0';
}
