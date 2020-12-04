/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cots.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:23:16 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/25 02:55:24 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			balance_checker(char **str, int balance, int *i)
{
	if ((*str)[(*i)] == '"' && balance != 2)
		balance = (balance > 0) ? 0 : 1;
	if ((*str)[(*i)] == '\'' && balance != 1)
		balance = (balance > 0) ? 0 : 2;
	if (((*str)[(*i)] == ' ') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 5;
	if (((*str)[(*i)] == '|') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 1;
	if (((*str)[(*i)] == ';') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 2;
	if (((*str)[(*i)] == '>') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 3;
	if (((*str)[(*i)] == '<') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 4;
	if (((*str)[(*i)] == '&') && (balance == 1 || balance == 2))
		(*str)[(*i)] = 6;
	return (balance);
}

int			open_cots_checker(char **str, int balance)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		balance = balance_checker(str, balance, &i);
		cut_quotas(str, &i, balance);
		i++;
	}
	return (balance);
}

void		joint(char **str, char *buff)
{
	char	*ptr;

	ptr = (*str);
	(*str) = ft_strjoin((*str), buff);
	ft_strdel(&ptr);
	ptr = ft_strrchr((*str), '\n');
	*ptr = '\0';
}

void		open_cots(char **str, int balance)
{
	char	*buff;
	char	*ptr;
	int		indice;

	indice = 0;
	while (1)
	{
		pr_writer(balance);
		get_next_line(0, &buff);
		if ((balance = open_cots_checker(&buff, balance)) == 0)
		{
			joint(str, buff);
			break ;
		}
		else
		{
			ptr = (*str);
			(*str) = ft_strjoin((*str), buff);
			ft_strdel(&ptr);
		}
		ft_strdel(&buff);
	}
	ft_strdel(&buff);
}
