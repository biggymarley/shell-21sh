/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:18:31 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/17 02:49:20 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void    free_list(t_cmd **cmd_list)
{
    free((*cmd_list)->cmd);
    if((*cmd_list)->red)
        {
            while((*cmd_list)->red)
            {
                (*cmd_list)->red->lfd = 0;
                (*cmd_list)->red->rfd = 0;
                (*cmd_list)->red->type = 0;
                free((*cmd_list)->red->file);
                (*cmd_list)->red = (*cmd_list)->red->next;
            }
        }
    if((*cmd_list)->pipe)
        free_list(&(*cmd_list)->pipe);
    if((*cmd_list)->sep)
        free_list(&(*cmd_list)->sep);
    ft_memdel((void **)cmd_list);
}