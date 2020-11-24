/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:48:47 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/23 22:37:53 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_deletlist(t_listp **alst, void (*del)(void *, size_t, void *))
{
	t_listp	*li;

	if (alst)
	{
		while (*alst)
		{
			li = (*alst)->next;
			ft_deletone(&(*alst), del);
			*alst = li;
		}
	}
}
