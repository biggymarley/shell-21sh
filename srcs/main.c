/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:25:56 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/29 05:46:55 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void print(t_cmd *cmd)
{
    puts("***CMD*****\n");
    ft_putendl(cmd->cmd);
    puts("********\n");
    if (cmd->red)
    {
        while (cmd->red)
        {
             puts("***LFD*****\n");
             ft_putnbr(cmd->red->lfd);
              puts("\n***********\n");
            puts("***FILE*****\n");
            ft_putendl(cmd->red->file);
            puts("***********\n");
             puts("***RFD*****\n");
             ft_putnbr(cmd->red->rfd);
              puts("\n***********\n");
            puts("***TYPE*****\n");
            ft_putnbr(cmd->red->type);
            puts("\n***********\n");
            cmd->red = cmd->red->next;
        }
    }
    if (cmd->pipe)
        print(cmd->pipe);
    if (cmd->sep)
        print(cmd->sep);
}

void free_red(t_red **red)
{
    t_red *ptr;

    while ((*red))
    {
        if ((*red)->file)
           ft_strdel(&(*red)->file);
        (*red)->lfd = 0;
        (*red)->rfd = 0;
        (*red)->type = 0;
        ptr = (*red);
        (*red) = (*red)->next;
        ft_memdel((void **)&ptr);
    }
    ft_memdel((void **)&red);
}

void free_cmd_list(t_cmd **cmd_line)
{
    ft_strdel(&(*cmd_line)->cmd);
    if ((*cmd_line)->red)
        free_red(&(*cmd_line)->red);
    if ((*cmd_line)->pipe)
        free_cmd_list(&(*cmd_line)->pipe);
    if ((*cmd_line)->sep)
        free_cmd_list(&(*cmd_line)->sep);
    ft_memdel((void **)cmd_line);
}

void core(t_env **env)
{
    char *buff;
    t_cmd *cmd_line;
    t_cmd **ptr;
    char *str;

    buff = NULL;
    str = NULL;
    while (1)
    {
        ft_putstr("\033[1;91mbiggyshell{v.200}$>\033[1;96m ");
        get_next_line(0, &buff);
        if ((cmd_line = parser(&buff)) == NULL)
        {
            ft_strdel(&buff);
            del_cmd_lst(&cmd_line);
            //ft_strdel(&str);
            continue;
        }
        if (!ft_strcmp(buff, "exit")) 
            break;
       // print(cmd_line);
        execute_cmd(cmd_line, env, 0);
        del_cmd_lst(&cmd_line);
        ft_strdel(&buff);
    }
    del_cmd_lst(&cmd_line);
    ft_strdel(&buff);
}

int main(int ac, char **av, char **environ)
{
    t_env *env;
    t_cmd *cmd_line;

    env = NULL;
    //printer();
    env_to_list(&env, environ);
    core(&env);
    free_env(&env, del);
    return (0);
}