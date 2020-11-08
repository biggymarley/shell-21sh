/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:02:23 by kbahrar           #+#    #+#             */
/*   Updated: 2020/11/07 23:04:02 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*index_line(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	s = ft_strnew(i + 1);
	if (!s)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

static int	return_read(int fd, char **str)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*temp;

	ret = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		temp = *str;
		*str = ft_strjoin(temp, buf);
		ft_strdel(&temp);
		if (ft_strchr(*str, '\n') != NULL)
			break ;
	}
	return (ret);
}

static char	*cach(char **str)
{
	char	*temp;

	temp = *str;
	*str = ft_strdup(ft_strchr(temp, '\n') + 1);
	ft_strdel(&temp);
	return (*str);
}

int			get_next_line(const int fd, char **line)
{
	int				ret;
	static char		*str[4096];
	char			buf[BUFF_SIZE + 1];

	ret = 0;
	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	if (!str[fd])
		str[fd] = ft_strnew(0);
	ret = return_read(fd, &str[fd]);
	if (!(ft_strlen(str[fd])) && ret == 0)
	{
		ft_strdel(&str[fd]);
		return (0);
	}
	*line = index_line(str[fd]);
	if (ft_strchr(str[fd], '\n') != NULL)
		cach(&str[fd]);
	else
		ft_strdel(&str[fd]);
	return (1);
}
