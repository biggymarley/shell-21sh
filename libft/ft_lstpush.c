/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 01:16:56 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/23 22:36:41 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listp		*ft_lstpush(t_listp **alst, t_listp *new)
{
	t_listp *head;

	head = *alst;
	if (!(head->content))
	{
		free(*alst);
		return (new);
	}
	else
	{
		while (head->next)
		{
			head = head->next;
		}
		head->next = new;
		new = NULL;
		return (*alst);
	}
}
