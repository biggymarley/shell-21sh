/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 20:25:30 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 23:03:16 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_whiteco(char const *s)
{
	int		i;
	int		rizilta;

	i = 0;
	rizilta = 0;
	while (s[i])
	{
		if (s[i] > 32 && (s[i + 1] <= 32 || s[i + 1] == '\0'))
		{
			i++;
			rizilta++;
		}
		else
			i++;
	}
	return (rizilta);
}

int			ft_countw(char const *s, char c)
{
	int		i;
	int		rizilta;

	i = 0;
	rizilta = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			i++;
			rizilta++;
		}
		else
			i++;
	}
	return (rizilta);
}
