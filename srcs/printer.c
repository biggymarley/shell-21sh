/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 02:56:04 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/21 23:33:25 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void printer()
{
    int fd;
    char *line;
    int c;
    int i;

    fd = open("asciimg/ascii.txt", O_RDONLY);
    c = 0;
    while(get_next_line(fd, &line))
    {
        i = 0;
        while(line[i] )
        {
            if(( c <= 9 || (c >= 36 && c <= 43)) &&  (line[i] == '(' || line[i] == ')' || line[i] == '.' ||  line[i] == '"'))
            {
                ft_putstr("\033[0;31m");
                ft_putchar(line[i]);
            }
            else if (c < 9 || c > 34)
            {
                ft_putstr("\033[1;34m");
                ft_putchar(line[i]);
            }
            else 
            {
                ft_putstr("\033[0;32m");
                ft_putchar(line[i]);
            }
            i++;
        }
            c++;
        usleep(60000);
    }
   close(fd);
   ft_putstr("\033[0m");
}