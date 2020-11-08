/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 03:48:10 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 02:06:30 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		ft_env(t_env *env)
{
	int		i;
	char	**nev;

	i = 0;
	nev = ltot(env);
	if (nev)
		while (nev[i])
			ft_putendl(nev[i++]);
	delkill(nev);
}
