/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 01:25:04 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/23 02:54:46 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	int		start;
	int		end;
	char	*tab;

	start = 0;
	end = 0;
	if (s)
	{
		while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
			start++;
		while (s[end])
			end++;
		end--;
		while (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')
			end--;
		tab = malloc(sizeof(char) * ft_count_size(s) + 1);
		if (tab)
		{
			ft_remplir(tab, s, start, end);
			return (tab);
		}
		return (NULL);
	}
	return (NULL);
}
