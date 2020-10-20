/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:49:16 by afaragi           #+#    #+#             */
/*   Updated: 2020/01/24 00:21:47 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_deletone(t_list **alst, void (*del)(void *, size_t, void *))
{
	if (alst)
	{
		del((*alst)->content, (*alst)->content_size, (*alst)->path);
		ft_memdel((void**)alst);
	}
}
