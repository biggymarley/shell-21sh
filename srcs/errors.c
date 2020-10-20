/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:16:01 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/17 03:14:03 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"


void    errors(int op, t_cmd **cmd_list)
{
    
    ft_putendl_fd("Shell: parse error", 2);
    free_list(cmd_list);
}