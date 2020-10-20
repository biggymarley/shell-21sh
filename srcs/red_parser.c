/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 05:01:11 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/20 06:55:25 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int right_big_red_checker(char *line, int i, char red1, char red2)
{
    int j;
    int checker;

    j = 0;
    ((line[i] == '<') ? (checker = 2) : (checker = 1));
    while (line[i] && j <= 3)
    {
        if (line[i] == red1)
            return (0);
        if (line[i] == red2 && j > checker)
            return (0);
        if (line[i] == '&' && j > 1)
            return (0);
        i++;
        j++;
    }
    return (1);
}

int left_big_red_checker(char *line, int i)
{
    int j;
    int checker;

    j = 0;
    ((line[i] == '<') ? (checker = 0) : (checker = 1));
    while (line[i] && j < 3)
    {
        i--;
        if (line[i] == '&' && j >= checker)
            return (0);
        j++;
    }
    return (1);
}

int red_checker(char *line, int i, char red1, char red2)
{
    int j;

    j = 0;
    if (!(right_big_red_checker(line, i, red1, red2)))
        return (0);
    if (!(left_big_red_checker(line, i)))
        return (0);
    return (1);
}

int red_errors_checker(char *line, int i)
{
    int type;

    ((line[i] == '<') ? (type = 1) : (type = -1));
    if (type == 1)
    {
        if (!(red_checker(line, i, '>', '<')))
        {
            ft_putendl_fd("21sh: parse error", 1);
            return (0);
        }
    }
    else if (type == -1)
    {
        if (!(red_checker(line, i, '<', '>')))
        {
            ft_putendl_fd("21sh: parse error", 1);
            return (0);
        }
    }
    return (1);
}

int fill_red_type(t_red **red_list, char *line, int i)
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
        return (0);
    return (1);
}

void red_fdclose_add(t_cmd **line, unsigned int *type, int index)
{
    if ((*line)->cmd[index + 1] && (*line)->cmd[index + 1] == ' ')
    {
        (*type) = (*type) | CLOSE_RFD;
        ft_move_replace(&(*line)->cmd[index]);
    }
}

int right_fd_filler(t_red **red_list, t_cmd **line, int i)
{
    int index;
    char *rfd;

    index = i + 2;
    while ((*line)->cmd[index] && ft_isdigit((*line)->cmd[index]))
        index++;
    if ((*line)->cmd[index] && (*line)->cmd[index] == '-' && (*red_list)->type & SWAP_LFD_TRFD)
        red_fdclose_add(line, &(*red_list)->type, index);
    if ((index == i + 2) || ((*line)->cmd[index] && (*line)->cmd[index] != ' '))
        return (0);
    rfd = ft_strdup_from_to((*line)->cmd, (i + 2), index);
    (*red_list)->rfd = (unsigned int)ft_atoi(rfd);
    free(rfd);
    index = i + 2;
    while ((*line)->cmd[index] && ft_isdigit((*line)->cmd[index]))
        ft_move_replace(&(*line)->cmd[index]);
    return (1);
}

int index_placer(t_red *red_list)
{
    if (red_list->type & (HERSTR))
        return (3);
    else if (red_list->type & (RED_STDOUT_ERR | READ_F_F | RED_TRUNC))
        return (1);
    else
        return (2);
}

int fd_file_filler(t_red **red_list, t_cmd **line, int *i)
{
    int index;
    int c;

    c = 0;
    index = (*i) + index_placer((*red_list));
    if (!(*line)->cmd[index])
    {
        ft_putendl("syntax error near unexpected token");
        return (0);
    }
    if ((*red_list)->type & (SWAP_LFD_TRFD | READ_FCUSFD))
        right_fd_filler(red_list, line, (*i));
    if ((*line)->cmd[index] && (*line)->cmd[index] == '-' && (*red_list)->type & (HERDOC))
        red_fdclose_add(line, &(*red_list)->type, index);
    while ((*line)->cmd[index] && (*line)->cmd[index] == ' ')
        index++;
    while ((*line)->cmd[index] && (*line)->cmd[index] != ' ')
    {
        c++;
        index++;
    }
    (*red_list)->file = ft_strdup_from_to((*line)->cmd, (*i) + index_placer((*red_list)), index);
    if (!(*red_list)->file[0] && !((*red_list)->type & (SWAP_LFD_TRFD | READ_FCUSFD)))
    {
        ft_putendl("syntax error near unexpected token");
        return (0);
    }
    return (1);
}

int red_parser(t_cmd **cmd_list)
{
    t_red **adr_list;
    int i;

    adr_list = &(*cmd_list)->red;
    i = 0;
    while ((*cmd_list)->cmd[i])
    {
        if ((*cmd_list)->cmd[i] == '>' || (*cmd_list)->cmd[i] == '<')
        {
            if (!(red_errors_checker((*cmd_list)->cmd, i)))
                return (0);
            (*adr_list) = (t_red *)ft_memalloc(sizeof(t_red));
            if (!(fill_red_type(&(*adr_list), (*cmd_list)->cmd, i)))
                return (0);
            if (!(fd_file_filler(&(*adr_list), cmd_list, &i)))
                return (0);
        }
        i++;
    }
    return (1);
}