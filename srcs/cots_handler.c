/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cots_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 22:29:03 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 01:25:15 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		rebase_all(char **cmd)
{
	rebase(cmd, 5, ' ');
	rebase(cmd, 1, '|');
	rebase(cmd, 2, ';');
	rebase(cmd, 3, '>');
	rebase(cmd, 4, '<');
	rebase(cmd, 6, '&');
}

void		rebase(char **cmd, char c, char b)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == c)
				cmd[i][j] = b;
			j++;
		}
		i++;
	}
}

void		cut_quotas(char **str, int *index, int balance)
{
	if ((*str)[(*index)] == '"' && (balance == 0 || balance == 1))
		ft_move_replace(&(*str)[(*index)--]);
	else if ((*str)[(*index)] == '\'' && (balance == 0 || balance == 2))
		ft_move_replace(&(*str)[(*index)--]);
}

void		pr_writer(int balance)
{
	if (balance == 1)
		write(1, "dquote> ", 8);
	else if (balance == 2)
		write(1, "quote> ", 7);
}

int			cots_check(char **str, int balance)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (*str);
	(*str) = ft_strtrim((*str));
	ft_strdel(&ptr);
	while ((*str)[i] != '\0')
	{
		balance = balance_checker(str, balance, &i);
		cut_quotas(str, &i, balance);
		i++;
	}
	if (balance == 0)
		return (-1);
	else
	{
		ptr = (*str);
		(*str) = ft_strjoin((*str), "\n");
		ft_strdel(&ptr);
		open_cots(str, balance);
	}
	return (balance);
}
