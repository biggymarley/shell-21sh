/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 04:37:20 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/28 03:50:31 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

t_fdcash				*ft_new(int fd)
{
	t_fdcash *li;

	if (!(li = (t_fdcash *)ft_memalloc(sizeof(t_fdcash))))
		return (NULL);
	li->fd = fd;
	if (!(li->cash = (char *)ft_memalloc((sizeof(char) * 1))))
		return (NULL);
	li->next = NULL;
	return (li);
}

t_fdcash				*ft_addfdsearch(int fd, t_fdcash **list)
{
	t_fdcash *li;
	t_fdcash *tmp;
	t_fdcash *head;

	if (!*list)
	{
		li = ft_new(fd);
		*list = li;
		return (li);
	}
	head = *list;
	while (head)
	{
		if (head->fd == fd)
			return (head);
		tmp = head;
		head = head->next;
	}
	li = ft_new(fd);
	tmp->next = li;
	return (li);
}

int						ft_line(t_fdcash *ptr, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	if (ptr->cash[i] == '\0')
		return (0);
	while (ptr->cash[i] != '\n' && ptr->cash[i] != '\0')
		i++;
	if (ptr->cash[i] != '\n')
	{
		*line = ptr->cash;
		ptr->cash = ft_strdup("\0");
		return (1);
	}
	ptr->cash[i] = '\0';
	*line = ft_strdup(ptr->cash);
	tmp = ptr->cash;
	ptr->cash = ft_strdup(&ptr->cash[i + 1]);
	free(tmp);
	return (1);
}

int						get_next_line(const int fd, char **line)
{
	int						nbread;
	static t_fdcash			*alst;
	char					*buff;
	char					*tmp;
	t_fdcash				*ptr;

	buff = NULL;
	if ((nbread = read(fd, buff, 0)) < 0 || !line)
		return (-1);
	if (!(buff = (char *)ft_memalloc((sizeof(char) * BUFF_SIZE + 1))))
		return (-1);
	ptr = ft_addfdsearch(fd, &alst);
	while (!ft_strchr(ptr->cash, '\n') &&
			(nbread = read(fd, buff, BUFF_SIZE) > 0))
	{
		tmp = ptr->cash;
		ptr->cash = ft_strjoin(ptr->cash, buff);
		ft_memset(buff, 0, BUFF_SIZE);
		free(tmp);
	}
	free(buff);
	if (!(ft_line(ptr, line)))
		return (0);
	return (1);
}
