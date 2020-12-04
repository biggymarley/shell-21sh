/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_pipe_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 04:43:33 by afaragi           #+#    #+#             */
/*   Updated: 2020/12/02 04:36:32 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int				single_cmd_parser(t_cmd **cmd_list, char *cmd, int i, int li)
{
	if (!((*cmd_list)->cmd = ft_strdup_from_to(cmd, li, i)))
	{
		errors(0, cmd_list);
		return (0);
	}
	else
	{
		if (!(red_parser(cmd_list)))
			return (0);
	}
	return (1);
}

int				sep_pipe_alloc(t_cmd **ct, char **cmd, int i, t_cmd **lp)
{
	if ((*cmd)[i] == '|')
	{
		if (!(pipe_parser(ct, cmd, i)))
			return (0);
	}
	else if ((*cmd)[i] == ';')
		if (!(sep_parser(ct, (*cmd), i, lp)))
			return (0);
	return (1);
}

int				check_init(char **cmd_line, t_parser *parser)
{
	(*parser).i = 0;
	(*parser).li = 0;
	(*parser).last_sep = NULL;
	(*parser).cmd_list = (t_cmd *)ft_memalloc(sizeof(t_cmd));
	(*parser).head = (*parser).cmd_list;
	(*parser).ptr = (*cmd_line);
	(*cmd_line) = ft_strtrim((*cmd_line));
	free((*parser).ptr);
	if (!(*cmd_line) && !ft_strlen((*cmd_line)))
	{
		ft_memdel((void **)&(*parser).cmd_list);
		return (0);
	}
	cots_check(cmd_line, 0);
	return (1);
}

int				core_parser(char **cmd_line, t_parser *p)
{
	if (!((*p).cmd_list->cmd = ft_strdup_from_to((*cmd_line), (*p).li, (*p).i)))
	{
		errors(0, &(*p).head);
		return (0);
	}
	if (!(red_parser(&(*p).cmd_list)))
		return (0);
	if (!(sep_pipe_alloc(&(*p).cmd_list, &(*cmd_line), (*p).i, &(*p).last_sep)))
	{
		errors(0, &(*p).head);
		return (0);
	}
	(*p).i++;
	(*p).li = (*p).i;
	return (1);
}

t_cmd			*parser(char **cmd_line)
{
	t_parser	p;

	if (!(check_init(cmd_line, &p)))
		return (NULL);
	while ((*cmd_line)[p.i])
	{
		if ((*cmd_line)[p.i] == '|' || (*cmd_line)[p.i] == ';')
		{
			if (!(core_parser(cmd_line, &p)))
			{
				return (NULL);
			}
			continue;
		}
		p.i++;
		if (!(*cmd_line)[p.i])
			if (!(single_cmd_parser(&p.cmd_list, (*cmd_line), p.i, p.li)))
				return (NULL);
	}
	return (p.head);
}
