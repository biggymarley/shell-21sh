/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:31:28 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/04 02:45:36 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void alias_checker(char **line)
{
    int i;
    int f;
    char *file;
    char *tmp;
    char *value;
    char **cmd;
    char **cc;

    f = open(".biggyrc", O_RDONLY);
    cmd = NULL;
    cc = ft_strsplit((*line), ' ');
    i = ft_strlen(cc[0]);
    while (get_next_line(f, &file) > 0)
    {
        tmp = file;
        file = ft_strtrim(file);
        free(tmp);
        if (file)
        {
            cmd = ft_strsplit(file, '=');
            if (!(ft_strcmp(cc[0], cmd[0])))
            {
                while (i)
                {
                    ft_move_replace((*line));
                    i--;
                }
                tmp = (*line);
                (*line) = ft_strjoin(cmd[1], (*line));
                free(tmp);
                ft_strdel(&file);
                delkill(cmd);
                delkill(cc);
                close(f);
                return;
            }
            delkill(cmd);
        }
        ft_strdel(&file);
    }
    close(f);
    delkill(cc);
}

void alias_parser(char **line)
{
    int i;
    int f;
    char *file;
    char *tmp;

    i = 1;
    file = NULL;
    if (!line[i])
    {
        f = open(".biggyrc", O_RDONLY, 0644);
        while (get_next_line(f, &file) > 0)
        {
            tmp = file;
            file = ft_strtrim(file);
            free(tmp);
            if (file[0] != '#')
                ft_putendl(file);
            ft_strdel(&file);
        }
    }
    else
    {
        f = open(".biggyrc", O_WRONLY | O_CREAT | O_APPEND, 0644);
        while (line[i])
        {
            ft_putendl_fd(line[i], f);
            i++;
        }
    }
    close(f);
}

void alias_editor(char **cmd)
{
}