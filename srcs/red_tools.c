/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 03:15:35 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/08 02:20:21 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			right_big_red_checker(char *line, int i, char red1, char red2)
{
	int		j;
	int		checker;
	int		indice;

	indice = 1;
	j = 0;
	checker = 1;
	(line[i] == '<') ? (checker = 2) : 0;
	while (line[i] && j <= 3)
	{
		((line[i] == '&') ? (indice = 2) : 0);
		if (line[i] != '&' && line[i] != '>' && line[i] != '<')
			return (indice);
		if (line[i] == red1)
			return (0);
		if (line[i] == red2 && j > checker)
			return (0);
		if (line[i] == '&' && j > 1)
			return (0);
		i++;
	}
	return (indice);
}

int			left_big_red_checker(char *line, int i, int indice)
{
	int		j;
	int		checker;

	j = 0;
	checker = 1;
	(line[i] == '<') ? (checker = 0) : 0;
	while (line[i] && j < 3)
	{
		i--;
		if ((indice == 2 && line[i] == '&') || (line[i] == '&' && j >= checker))
			return (0);
		j++;
	}
	return (1);
}

int			red_checker(char *line, int i, char red1, char red2)
{
	int		indice;

	if (!(indice = right_big_red_checker(line, i, red1, red2)))
		return (0);
	if (!(left_big_red_checker(line, i, indice)))
		return (0);
	return (1);
}

int			red_errors_checker(char *line, int i)
{
	int		type;

	type = -1;
	(line[i] == '<') ? (type = 1) : 0;
	if (type == 1)
	{
		if (!(red_checker(line, i, '>', '<')))
			return (0);
	}
	else if (type == -1)
	{
		if (!(red_checker(line, i, '<', '>')))
			return (0);
	}
	return (1);
}

int			fill_red_type(t_red **red_list, char *line, int i)
{
	if (!ft_strncmp(&line[i], "<<<", ft_strlen("<<<")))
		(*red_list)->type = HERSTR;
	else if (!ft_strncmp(&line[i], "<<", ft_strlen("<<")))
		(*red_list)->type = HERDOC;
	else if (!ft_strncmp(&line[i], ">&", ft_strlen(">&")))
		(*red_list)->type = SWAP_LFD_TRFD;
	else if (i && !ft_strncmp(&line[i - 1], "&>", ft_strlen("&>")))
		(*red_list)->type = RED_STDOUT_ERR;
	else if (!ft_strncmp(&line[i], "<&", ft_strlen("<&")))
		(*red_list)->type = READ_FCUSFD;
	else if (!ft_strncmp(&line[i], ">>", 2))
		(*red_list)->type = RED_APPND;
	else if (!ft_strncmp(&line[i], "<", 1))
		(*red_list)->type = READ_F_F;
	else if (!ft_strncmp(&line[i], ">", 1))
		(*red_list)->type = RED_TRUNC;
	else
	{
		ft_putendl_fd("\a21sh: parse error", 2);
		return (0);
	}
	return (1);
}
