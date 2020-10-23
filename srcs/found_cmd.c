/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 23:28:50 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/23 03:51:17 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void delkill(char **paths)
{
    int i;

    i = 0;
    if (paths)
    {
        while (paths[i])
            free(paths[i++]);
       //ft_memdel((void **)paths);
       free(paths);
    }
}

t_env *search_env(t_env *env, char *name)
{
    t_env *ptr;
    int i;

    i = 0;
    ptr = env;
    if (ptr)
    {
        while (ptr && ptr->name)
        {
            if (ft_strcmp(ptr->name, name) == 0)
                return (ptr);
            ptr = ptr->next;
        }
    }
    return (NULL);
}

int check(t_env **lst, char *str)
{
    if (ft_strchr(str, '/'))
        if (access(str, F_OK) == 0)
            return (1);
    *lst = search_env(*lst, "PATH");
    return (0);
}

void error_cmd(char *cmd, char *str)
{
    if (!str)
    {
        ft_putstr_fd("SHELL: command not found: ", 2);
        ft_putendl_fd(cmd, 2);
    }
}

char **found_func(t_env *lst, char *cmd, char **str)
{
    char **paths;
    char *tmp;
    int i;

    i = -1;
    if (check(&lst, str[0]) == 1)
        return (str);
    if (lst == NULL)
        return (NULL);
    paths = ft_strsplit(lst->value, ':');
    while (paths[++i])
    {
        tmp = paths[i];
        paths[i] = ft_strjoin(paths[i], "/");
        free(tmp);
        tmp = paths[i];
        paths[i] = ft_strjoin(paths[i], cmd);
        free(tmp);
        if (access(paths[i], F_OK) == 0)
            break;
    }
    error_cmd(str[0], paths[i]);
    free(str[0]);
    str[0] = ft_strdup(paths[i]);
    delkill(paths);
    return (str);
}