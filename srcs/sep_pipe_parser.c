/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_pipe_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 04:43:33 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/23 05:13:39 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int pipe_parser(t_cmd **cmd_list, char **cmd, int i)
{
    if ((*cmd_list)->cmd == NULL)
    {
        errors(0, cmd_list);
        return (0);
    }
    (*cmd_list)->pipe = (t_cmd *)ft_memalloc(sizeof(t_cmd));
    (*cmd_list) = (*cmd_list)->pipe;
    if (!(*cmd)[i + 1] && i > 0)
        pipe_reader(cmd);
    return (1);
}

int sep_parser(t_cmd **cmd_list, char *cmd, int i, t_cmd **last_sep)
{

    if ((*cmd_list)->cmd == NULL)
    {
        errors(0, cmd_list);
        return (0);
    }
    if ((*last_sep) != NULL)
        (*cmd_list) = (*last_sep);
    (*cmd_list)->sep = (t_cmd *)ft_memalloc(sizeof(t_cmd));
    (*last_sep) = (*cmd_list)->sep;
    (*cmd_list) = (*cmd_list)->sep;
    return (1);
}

int single_cmd_parser(t_cmd **cmd_list, char *cmd, int i, int last_index)
{
    if (!((*cmd_list)->cmd = ft_strdup_from_to(cmd, last_index, i)))
    {
        errors(0, cmd_list);
        return (0);
    }
    else
    {
        if(!(red_parser(cmd_list)))
                return(0);
    }
    return (1);
}

int sep_pipe_alloc(t_cmd **cmd_list, char **cmd, int i, t_cmd **last_sep)
{

    if ((*cmd)[i] == '|')
    {
        if (!(pipe_parser(cmd_list, cmd, i)))
            return (0);
    }
    else if ((*cmd)[i] == ';')
        if (!(sep_parser(cmd_list, (*cmd), i, last_sep)))
            return (0);
    return(1);
}

t_cmd *parser(char *cmd_line)
{
    int i;
    int last_index;
    t_cmd *cmd_list;
    t_cmd *head;
    t_cmd *last_sep;

    i = 0;
    last_index = 0;
    last_sep = NULL;
    cmd_list = (t_cmd *)ft_memalloc(sizeof(t_cmd));
    head = cmd_list;
    if(cmd_line && cmd_line[0] == '\0')
        return(NULL);
    while (cmd_line[i])
    {
        if (cmd_line[i] == '|' || cmd_line[i] == ';')
        {
            if (!(cmd_list->cmd = ft_strdup_from_to(cmd_line, last_index, i)))
            {
                errors(0, &cmd_list);
                return (NULL);
            }
            if(!(red_parser(&cmd_list)))
                return(NULL);
            if(!(sep_pipe_alloc(&cmd_list, &cmd_line, i, &last_sep)))
            {
                errors(0, &cmd_list);

                return (NULL);
            }
            i++;
            last_index = i;
            continue;
        }
        i++;
        if (!cmd_line[i])
            if (!(single_cmd_parser(&cmd_list, cmd_line, i, last_index)))
                return (NULL);
    }
    return (head);
}