/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:16:01 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 04:07:11 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void	errors(int op, t_cmd **cmd_list)
{
	ft_putendl_fd("\aShell: parse error", 2);
	del_cmd_lst(cmd_list);
}
