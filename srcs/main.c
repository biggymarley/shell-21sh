/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:25:56 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/20 05:25:15 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void print(t_cmd *cmd)
{
    ft_putendl(cmd->cmd);
    if(cmd->pipe)
        print(cmd->pipe);
    if(cmd->sep)
        print(cmd->sep);
}

void core()
{
    char buff[1000];
    t_cmd *cmd_line;

    while (1)
    {
        ft_putstr("\033[1;91mbiggyshell{v.200}$>\033[1;96m ");
        read(1, (void *)buff, 1000);
        
        if ((cmd_line = parser(ft_strtrim((char *)buff))) == NULL)
        {
            ft_strclr(buff);
            continue;
        }
        print(cmd_line);
        ft_strclr(buff);
    }
}

int main(int ac, char **av, char **environ)
{
    t_env *env;
    t_cmd *cmd_line;

    env = NULL;
    env_to_list(&env, environ);
    core();
    return (0);
}