/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 23:10:24 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/30 04:38:03 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int if_bult(char **str)
{
    if (str)
    {
        if (ft_strcmp(str[0], "exit") == 0 ||
            ft_strcmp(str[0], "EXIT") == 0)
            return (1);
        else if (ft_strcmp(str[0], "setenv") == 0 ||
                 ft_strcmp(str[0], "SETENV") == 0)
            return (2);
        else if (ft_strcmp(str[0], "unsetenv") == 0 ||
                 ft_strcmp(str[0], "UNSETENV") == 0)
            return (6);
        else if (ft_strcmp(str[0], "env") == 0 ||
                 ft_strcmp(str[0], "ENV") == 0)
            return (3);
        else if (ft_strcmp(str[0], "cd") == 0 ||
                 ft_strcmp(str[0], "CD") == 0)
            return (4);
        else if (ft_strcmp(str[0], "echo") == 0 ||
                 ft_strcmp(str[0], "ECHO") == 0)
            return (5);
    }
    return (0);
}

char **cmd_finder(t_env *env, char *cmd)
{
    char **line;
    char *ptr;
    char **tmp;

    if (cmd)
    {
        ptr = ft_strtrim(cmd);
        if (ptr[0] == '\0')
        {
            ft_strdel(&ptr);
            return (NULL);
        }
        line = ft_strsplit(ptr, ' ');
        rebase_all(line);
        tmp = found_func(env, line[0], line);
        ft_strdel(&ptr);
    }
    return (tmp);
}

int fdhandler(int cmd_nbr, int fd_handler, int *fd, t_cmd *cmd_list)
{
    if (cmd_nbr != 0)
        dup2(fd_handler, 0);
    if (cmd_list->pipe)
        dup2(fd[1], 1);
    close(fd[0]);
    close(fd[1]);
    close(fd_handler);
    if (cmd_list->red)
        if (!red_duper(cmd_list->red))
            return(0);
    return(1);
}

int duplicate_and_execute(char **cmd, t_env **env, int cmd_nbr, t_cmd *cmd_list)
{
    int built_cmd;
    static int fd_handler;
    char **nev;
    int fd[2];

    nev = NULL;
    if(!cmd && !cmd_list && !cmd_nbr && !env)
    {
        close(fd_handler);
        return(1);
    }
    built_cmd = if_bult(cmd);
    nev = ltot((*env));
    if (pipe(fd) == -1)
        return (0);
    else if (!fork())
    {
        if(!(fdhandler(cmd_nbr, fd_handler, fd, cmd_list)))
            exit(EXIT_FAILURE);
        execve(cmd[0], cmd, nev);
        exit(1);
    }
    close(fd[1]);
    if (cmd_nbr != 0)
        close(fd_handler);
    fd_handler = fd[0];
    delkill(nev);
    return (1);
}

int execute_cmd(t_cmd *cmd_list, t_env **env, int cmd_nbr)
{
    char **cmd;
    int fd;

    cmd = NULL;
    if (!(cmd = cmd_finder((*env), cmd_list->cmd)) && !cmd_list->red)
    {
        delkill(cmd);
        return (0);
    }
    if (cmd && !cmd[0] && !cmd_list->red)
    {
        delkill(cmd);
        return (0);
    }
    duplicate_and_execute(cmd, env, cmd_nbr, cmd_list);
    delkill(cmd);
    if (cmd_list->pipe)
        execute_cmd(cmd_list->pipe, env, cmd_nbr + 1);
    else
    {
        duplicate_and_execute(NULL, 0, 0, 0);
        while (wait(NULL) > 0)
        {
        }
    }
    if (cmd_list->sep)
        execute_cmd(cmd_list->sep, env, 0);
    return (1);
}