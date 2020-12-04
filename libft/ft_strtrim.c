/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 01:25:04 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/02 04:18:37 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_skip_sep(const char *str, char *sep)
{
	int i;
	int j;
	int count_sep;

	count_sep = 0;
	j = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (sep[j])
		{
			if (str[count_sep] == sep[j] || str[count_sep] < 0)
				count_sep++;
			j++;
		}
		i++;
	}
	return (count_sep);
}

int		ft_skip_lensep(char const *str, char *sp)
{
	int i;
	int count;
	int j;

	count = 0;
	i = ft_strlen(str) - 1;
	count = ft_strlen(str) - 1;
	if (str)
		while (str[i])
		{
			j = 0;
			while (sp[j])
			{
				if (str[count] == sp[j])
					count--;
				j++;
			}
			i--;
		}
	return (count);
}

int			ft_count_char(char const *str)
{
	int i;
	int count_size;
	int j;

	j = 0;
	i = 0;
	count_size = 0;
	if (str)
	{
		while (str[i] == '\n' || str[i] == '\t' || str[i] == ' ')
			i++;
		while (str[j] != '\0')
			j++;
		j--;
		while (str[j] == '\n' || str[j] == '\t' || str[j] == ' ')
			j--;
		while (i <= j)
		{
			count_size++;
			i++;
		}
		return (count_size);
	}
	return (0);
}

char	*ft_strtrim(char const *s)
{
	int			i;
	char		*str;
	int			j;
	int			k;

	k = 0;
	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * ft_count_char(s) + 1)))
		return (NULL);
	j = ft_skip_lensep(s, " \n\t");
	i = ft_skip_sep(s, " \n\t");
	if (s[j] == '\\' && s[j + 1])
		j++;
	while (i <= j)
		str[k++] = s[i++];
	str[k] = '\0';
	return (str);
}
