/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:18:31 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/23 05:38:46 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void del_cmd_lst(t_cmd **cmd)
{
    t_red *ptr;
    
    if ((*cmd))
    {
        free((*cmd)->cmd);
        if ((*cmd)->red)
        {
            while ((*cmd)->red)
            {
                free((*cmd)->red->file);
                (*cmd)->red->lfd = 0;
                (*cmd)->red->rfd = 0;
                (*cmd)->red->type = 0;
                ptr = (*cmd)->red;
                (*cmd)->red = (*cmd)->red->next;
                ft_memdel((void **)&ptr);
            }
            ft_memdel((void **)&(*cmd)->red);
        }
        if ((*cmd)->sep)
        {
            del_cmd_lst(&(*cmd)->sep);
        }
        if ((*cmd)->pipe)
            del_cmd_lst(&(*cmd)->pipe);
        ft_memdel((void **)cmd);
    }
}