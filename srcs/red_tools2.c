/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 03:17:00 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/08 02:21:10 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		red_fdclose_add(t_cmd **line, unsigned int *type, int index)
{
	(*type) = (*type) | CLOSE_RFD;
	ft_move_replace(&(*line)->cmd[index]);
}

int			right_fd_filler(t_red **red_list, t_cmd **line, int i)
{
	int		index;
	char	*rfd;

	index = i + 2;
	while ((*line)->cmd[index] && ft_isdigit((*line)->cmd[index]))
		index++;
	if ((*line)->cmd[index] && (*line)->cmd[index] == '-' &&
		(*red_list)->type & (SWAP_LFD_TRFD | HERDOC))
	{
		if (!(*line)->cmd[index + 1] && (*red_list)->type & HERDOC)
			return (-1);
		red_fdclose_add(line, &(*red_list)->type, index);
	}
	if (index == i + 2 || (*red_list)->type & (HERDOC))
	{
		(*red_list)->rfd = 0;
		return (0);
	}
	rfd = ft_strdup_from_to((*line)->cmd, (i + 2), index);
	(*red_list)->rfd = (unsigned int)ft_atoi(rfd);
	free(rfd);
	index = i + 2;
	while ((*line)->cmd[index] && ft_isdigit((*line)->cmd[index]))
		ft_move_replace(&(*line)->cmd[index]);
	return (1);
}

int			index_placer(t_red *red_list)
{
	if (red_list->type & (HERSTR))
		return (3);
	else if (red_list->type & (RED_STDOUT_ERR | READ_F_F | RED_TRUNC))
		return (1);
	else
		return (2);
}

void		strdup_clean(t_red **red_list, t_cmd **line, int *index, int *i)
{
	int		c;
	int		p;
	char	*ptr;

	while ((*line)->cmd[(*index)] && (*line)->cmd[(*index)] == ' ')
		(*index)++;
	c = (*index);
	while ((*line)->cmd[(*index)] && (*line)->cmd[(*index)] != ' ' &&
		(*line)->cmd[(*index)] != '>' && (*line)->cmd[(*index)] != '<'
			&& (*line)->cmd[(*index)] != '&')
		(*index)++;
	p = index_placer((*red_list));
	(*red_list)->file = ft_strdup_from_to((*line)->cmd, (*i) + p, (*index));
	ptr = (*red_list)->file;
	(*red_list)->file = ft_strtrim((*red_list)->file);
	free(ptr);
	while ((*line)->cmd[c] && (*line)->cmd[c] != ' ')
	{
		ft_move_replace(&(*line)->cmd[c]);
		if ((*line)->cmd[c] == '<' || (*line)->cmd[c] == '>'
			|| (*line)->cmd[c] == '&')
			return ;
	}
}

void		red_cleaner(t_red **red_list, int *start, t_cmd **line)
{
	int		counter;

	counter = index_placer((*red_list));
	if ((*red_list)->type & (RED_STDOUT_ERR))
	{
		(*start) = (*start) - 1;
		counter++;
	}
	while ((*line)->cmd[(*start)] && (*line)->cmd[(*start)] != ' ')
	{
		ft_move_replace(&(*line)->cmd[(*start)]);
		counter--;
		if (!counter)
			if ((*line)->cmd[(*start)] == '>' || (*line)->cmd[(*start)] == '<'
				|| (*line)->cmd[(*start)] == '&')
				return ;
	}
}
