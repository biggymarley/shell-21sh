/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cots_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 22:29:03 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/29 01:54:26 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void rebase_all(char **cmd)
{
    rebase(cmd, 5, ' ');
    rebase(cmd, 1, '|');
    rebase(cmd, 2, ';');
    rebase(cmd, 3, '>');
    rebase(cmd, 4, '<');
    rebase(cmd, 6, '&');
}

void rebase(char **cmd, char c, char b)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (cmd[i])
    {
        j = 0;
        while (cmd[i][j])
        {
            if (cmd[i][j] == c)
                cmd[i][j] = b;
            j++;
        }
        i++;
    }
}

void cut_quotas(char **str, int *index, int balance)
{
    if ((*str)[(*index)] == '"' && (balance == 0 || balance == 1))
        ft_move_replace(&(*str)[(*index)--]);
    else if ((*str)[(*index)] == '\'' && (balance == 0 || balance == 2))
        ft_move_replace(&(*str)[(*index)--]);
}

void pr_writer(int balance)
{
    if (balance == 1)
        write(1, "dquote> ", 8);
    else if (balance == 2)
        write(1, "quote> ", 7);
}

int balance_checker(char **str, int balance, int *i)
{
    if ((*str)[(*i)] == '"' && balance != 2)
        balance = (balance > 0) ? 0 : 1;
    if ((*str)[(*i)] == '\'' && balance != 1)
        balance = (balance > 0) ? 0 : 2;
    if (((*str)[(*i)] == ' ') && (balance == 1 || balance == 2))
        (*str)[(*i)] = 5;
    if (((*str)[(*i)] == '|') && (balance == 1 || balance == 2))
        (*str)[(*i)] = 1;
    if (((*str)[(*i)] == ';') && (balance == 1 || balance == 2))
        (*str)[(*i)] = 2;
    if (((*str)[(*i)] == '>') && (balance == 1 || balance == 2))
        (*str)[(*i)] = 3;
    if (((*str)[(*i)] == '<') && (balance == 1 || balance == 2))
        (*str)[(*i)] = 4;
    if (((*str)[(*i)] == '&') && (balance == 1 || balance == 2))
        (*str)[(*i)] = 6;
    return (balance);
}

int open_cots_checker(char **str, int balance)
{
    int i;

    i = 0;
    while ((*str)[i])
    {
        balance = balance_checker(str, balance, &i);
        cut_quotas(str, &i, balance);
        i++;
    }
    return (balance);
}

void open_cots(char **str, int balance)
{
    char *buff;
    char *ptr;
    int indice;

    indice = 0;
    while (1)
    {
        pr_writer(balance);
        get_next_line(0, &buff);
        if ((balance = open_cots_checker(&buff, balance)) == 0)
        {
            ptr = (*str);
            (*str) = ft_strjoin((*str), buff);
            ft_strdel(&ptr);
            ptr = ft_strrchr((*str), '\n');
            *ptr = '\0';
            break;
        }
        else
        {
            ptr = (*str);
            (*str) = ft_strjoin((*str), buff);
            ft_strdel(&ptr);
        }
        ft_strdel(&buff);
    }
    ft_strdel(&buff);
}

int cots_check(char **str, int balance)
{
    int i;
    char *ptr;

    i = 0;
    ptr = (*str);
    (*str) = ft_strtrim((*str));
    ft_strdel(&ptr);
    while ((*str)[i] != '\0')
    {
        balance = balance_checker(str, balance, &i);
        cut_quotas(str, &i, balance);
        i++;
    }
    if (balance == 0)
        return (-1);
    else
    {
        ptr = (*str);
        (*str) = ft_strjoin((*str), "\n");
        ft_strdel(&ptr);
        open_cots(str, balance);
    }
    return (balance);
}