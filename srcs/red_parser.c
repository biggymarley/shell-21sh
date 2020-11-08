/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 05:01:11 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/08 02:21:51 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		clear_lfd(t_cmd **line, int index, int counter)
{
	while ((*line)->cmd[index] && (*line)->cmd[index] != ' ')
	{
		ft_move_replace(&(*line)->cmd[index]);
		counter--;
		if (!counter)
			if ((*line)->cmd[index] == '>' || (*line)->cmd[index] == '<'
				|| (*line)->cmd[index] == '&')
				return ;
	}
}

void		left_fd_filler(int *i, t_cmd **line, t_red **red_list)
{
	int		index;
	char	*lfd;
	int		counter;

	index = (*i) - 1;
	while (index && (*line)->cmd[index] && ft_isdigit((*line)->cmd[index]))
		index--;
	if (index && (index == ((*i) - 1) || (*red_list)->type & RED_STDOUT_ERR))
	{
		if ((*red_list)->type & (RED_TRUNC | RED_APPND | SWAP_LFD_TRFD))
			(*red_list)->lfd = 1;
		else
			(*red_list)->lfd = 0;
		red_cleaner(red_list, i, line);
		return ;
	}
	if (index)
		index = index + 1;
	lfd = ft_strdup_from_to((*line)->cmd, index, (*i));
	(*red_list)->lfd = (unsigned int)ft_atoi(lfd);
	free(lfd);
	counter = index_placer((*red_list));
	counter = counter + ((*i) - index);
	clear_lfd(line, index, counter);
}

int			fd_file_filler(t_red **red_list, t_cmd **line, int *i)
{
	int		index;
	int		c;

	c = 0;
	index = (*i) + index_placer((*red_list));
	if (!(*line)->cmd[index])
		return (0);
	if ((*red_list)->type & (SWAP_LFD_TRFD | READ_FCUSFD | HERDOC))
		if (right_fd_filler(red_list, line, (*i)) < 0)
			return (0);
	if (!((*red_list)->type & (SWAP_LFD_TRFD | READ_FCUSFD)))
		strdup_clean(red_list, line, &index, i);
	left_fd_filler(i, line, red_list);
	if (!((*red_list)->type & (SWAP_LFD_TRFD | READ_FCUSFD))
		&& !(*red_list)->file)
		return (0);
	if ((*red_list)->type & HERDOC)
		read_herdoc((*red_list));
	return (1);
}

int			parse_red(t_cmd **cmd_list, t_red **adr_list, int i)
{
	if ((*adr_list))
	{
		while ((*adr_list))
			adr_list = &(*adr_list)->next;
	}
	if (!(red_errors_checker((*cmd_list)->cmd, i)))
	{
		ft_putendl_fd("\a21sh: parse error", 2);
		return (0);
	}
	(*adr_list) = (t_red *)ft_memalloc(sizeof(t_red));
	if (!(fill_red_type(&(*adr_list), (*cmd_list)->cmd, i)))
		return (0);
	if (!(fd_file_filler(&(*adr_list), cmd_list, &i)))
	{
		ft_putendl_fd("\asyntax error near unexpected token", 2);
		return (0);
	}
	return (1);
}

int			red_parser(t_cmd **cmd_list)
{
	t_red	**adr_list;
	int		i;

	adr_list = &(*cmd_list)->red;
	(*adr_list) = NULL;
	i = 0;
	while ((*cmd_list)->cmd[i])
	{
		if ((*cmd_list)->cmd[i] == '>' || (*cmd_list)->cmd[i] == '<')
		{
			if (!(parse_red(cmd_list, adr_list, i)))
				return (0);
			continue;
		}
		i++;
	}
	return (1);
}
