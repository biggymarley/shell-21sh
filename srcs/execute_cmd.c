/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 23:10:24 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/04 02:41:35 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

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
        if(!if_bult(line))
            line = found_func(env, line[0], line);
        ft_strdel(&ptr);
    }
    return (line);
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
            return (0);
    return (1);
}

int duplicate_and_execute(char **cmd, t_env **env, int cmd_nbr, t_cmd *cmd_list)
{
    int built_cmd;
    static int fd_handler;
    char **nev;
    int fd[2];

    nev = NULL;
    if (!cmd && !cmd_list && !cmd_nbr && !env)
    {
        close(fd_handler);
        return (1);
    }
    if ((built_cmd = if_bult(cmd)))
        execve_built(cmd[0], cmd, env, built_cmd);
    nev = ltot((*env));
    if (pipe(fd) == -1)
    {
        delkill(nev);
        return (0);
    }
    else if (!fork())
    {
        if (!(fdhandler(cmd_nbr, fd_handler, fd, cmd_list)))
            exit(EXIT_FAILURE);
        if (!built_cmd)
            execve(cmd[0], cmd, nev);
        else if (built_cmd)
            execve_builts_in_child(cmd[0], cmd, env, built_cmd);
        exit(1);
    }
    delkill(nev);
    close(fd[1]);
    if (cmd_nbr != 0)
        close(fd_handler);
    fd_handler = fd[0];
    return (1);
}

int execute_cmd(t_cmd *cmd_list, t_env **env, int cmd_nbr)
{
    char **cmd;
    int fd;

    cmd = NULL;
    alias_checker(&cmd_list->cmd);
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