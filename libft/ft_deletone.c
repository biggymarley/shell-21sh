/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:49:16 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/23 22:35:58 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_deletone(t_listp **alst, void (*del)(void *, size_t, void *))
{
	if (alst)
	{
		del((*alst)->content, (*alst)->content_size, (*alst)->path);
		ft_memdel((void**)alst);
	}
}
