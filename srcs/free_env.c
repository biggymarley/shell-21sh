/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 05:08:15 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/23 03:44:40 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void del(void *s, void *str)
{
    free(s);
    free(str);
}

void		ft_one_envdel(t_env **alst, void (*del)(void *, void *))
{
	if (alst)
	{
		del((*alst)->name, (*alst)->value);
		ft_memdel((void**)alst);
	}
}

void		free_env(t_env **alst, void (*del)(void *, void *))
{
	t_env	*li;

	if (alst)
	{
		while (*alst)
		{
			li = (*alst)->next;
			ft_one_envdel(&(*alst), del);
			*alst = li;
		}
	}
}