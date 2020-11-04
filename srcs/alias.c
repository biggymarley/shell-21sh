/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:31:28 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/04 05:03:36 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int alias_checker(char **line)
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
            if (cmd && cmd[0] && !(ft_strcmp(cc[0], cmd[0])) && cmd[1])
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
                return (-1);
            }
            delkill(cmd);
        }
        ft_strdel(&file);
    }
    close(f);
    delkill(cc);
    return (1);
}

int alias_check(char **line)
{
    int f;
    char *file;
    char *tmp;
    char *value;
    char **cmd;
    char **cc;

    f = open(".biggyrc", O_RDONLY);
    cmd = NULL;
    cc = ft_strsplit((*line), '=');
    if (!cc[1])
    {
        ft_putendl_fd("alias : format error", 2);
        return (-1);
    }
    while (get_next_line(f, &file) > 0)
    {
        tmp = file;
        file = ft_strtrim(file);
        free(tmp);
        if (file)
        {
            cmd = ft_strsplit(file, '=');
            if (cmd && cmd[0] && !(ft_strcmp(cc[0], cmd[0])))
            {
                ft_putendl_fd("alias already exist try an other", 2);
                delkill(cmd);
                return (-1);
            }
            delkill(cmd);
        }
        ft_strdel(&file);
    }
    close(f);
    delkill(cc);
    return (1);
}

void alias_parser(char **line)
{
    int i;
    int f;
    char *file;
    char *tmp;

    i = 1;
    file = NULL;
    if (counter(line) > 2)
    {
        ft_putendl_fd("alias : too many arguments", 2);
        return;
    }
    if (!line[i])
    {
        f = open(".biggyrc", O_RDONLY, 0644);
        while (get_next_line(f, &file) > 0)
        {
            tmp = file;
            file = ft_strtrim(file);
            free(tmp);
            if (file && file[0] && file[0] != '#')
                ft_putendl(file);
            ft_strdel(&file);
        }
    }
    else
    {
        f = open(".biggyrc", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if ((alias_check(&line[i])) > 0)
            ft_putendl_fd(line[i], f);
    }
    close(f);
}
