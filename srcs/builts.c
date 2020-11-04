/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 03:40:00 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/03 23:43:15 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int is_num(char *str)
{
    int i;

    i = 0;
    if (str)
    {
        while (str[i])
        {
            if (ft_isdigit(str[i]) == 0)
                return (0);
            i++;
        }
    }
    return (1);
}

int ft_exit(char **str)
{
    int num;
    int c;

    c = counter(str);
    if (is_num(str[1]) == 0)
    {
        ft_putstr_fd(": exit: ", 2);
        ft_putstr_fd(str[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        return (-1337);
    }
    if (c > 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        return (-1337);
    }
    ft_putstr("exit\n");
    if (c == 1)
        return (0);
    num = ft_atoi(str[1]);
    return (num);
}

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
        else if (ft_strcmp(str[0], "alias") == 0 ||
                 ft_strcmp(str[0], "ALIAS") == 0)
            return (7);
    }
    return (0);
}

void execve_built(char *cmd, char **line, t_env **env, int cmdnbr)
{
    if (cmdnbr == 4)
        ft_cd(line, env);
    else if (cmdnbr == 2)
        ft_setenv(env, line);
    else if (cmdnbr == 6)
        delete_env_var(env, line);
}

void execve_builts_in_child(char *cmd, char **line, t_env **env, int cmdnbr)
{
    if (cmdnbr == 5)
        ft_echo(line);
    else if (cmdnbr == 3)
        ft_env(*env);
    else if (cmdnbr == 7)
        alias_parser(line);
}