/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 01:51:26 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/23 02:25:40 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int exec_red(t_red *red, int *f)
{
    if (red->type & (RED_TRUNC | RED_STDOUT_ERR))
        (*f) = open(red->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    else if (red->type & READ_F_F)
    {
        if (((*f) = open(red->file, O_RDONLY)) < 0)
        {
            ft_putstr_fd(red->file, 2);
            ft_putendl_fd(": No such file or directory", 2);
            return (0);
        }
    }
    else if (red->type & RED_APPND)
        (*f) = open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    return (1);
}

void fd_handler_red(t_red *red, int fd_handler, int a, int indice)
{
    if (indice == 2)
    {
        dup2(fd_handler, 1);
        dup2(fd_handler, 2);
    }
    else if (indice == 3)
        dup2(red->rfd, red->lfd);
    else
    {
        if (red->lfd)
            dup2(fd_handler, red->lfd);
        else
            dup2(fd_handler, a);
    }
    if (!indice || indice == 2)
        close(fd_handler);
}

int red_duper(t_red *red)
{
    int fd_handler;
    int fd[2];

    if (pipe(fd) == -1)
        return (0);
    while (red)
    {

        if (!exec_red(red, &fd_handler))
            return (0);
        if (red->type & READ_F_F)
            fd_handler_red(red, fd_handler, 0, 0);
        else if (red->type & (RED_TRUNC | RED_APPND))
            fd_handler_red(red, fd_handler, 1, 0);
        else if (red->type & (HERSTR | HERDOC))
        {
            ft_putendl_fd(red->file, fd[1]);
            fd_handler_red(red, fd[0], 0, 1);
        }
        else if (red->type & RED_STDOUT_ERR)
            fd_handler_red(red, fd_handler, 0 , 2);
        else if (red->type & SWAP_LFD_TRFD)
            fd_handler_red(red, 0 ,0, 3);
        fd_handler = 0;
        red = red->next;
    }
    close(fd[1]);
    close(fd[0]);
    return(1);
}