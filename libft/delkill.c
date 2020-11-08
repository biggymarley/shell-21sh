/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delkill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 03:53:11 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 03:53:23 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			delkill(char **paths)
{
	int			i;

	i = 0;
	if (paths)
	{
		if (paths[i])
		{
			while (paths[i])
				ft_strdel(&paths[i++]);
		}
		free(paths);
		paths = NULL;
	}
}
