/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 01:08:52 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/23 22:36:01 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_listp **alst, void (*del)(void *, size_t))
{
	t_listp	*li;

	if (alst)
	{
		while (*alst)
		{
			li = (*alst)->next;
			ft_lstdelone(&(*alst), del);
			*alst = li;
		}
	}
}
