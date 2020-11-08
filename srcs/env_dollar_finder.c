/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dollar_finder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 04:50:56 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 04:58:33 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

t_env		*env_dollar_finder(t_env *env, char *name)
{
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = env;
	if (ptr)
	{
		while (ptr && ptr->name)
		{
			while (name[i] && (ft_isalnum(name[i]) || name[i] == '_'))
				i++;
			if (ft_strncmp(ptr->name, name, i) == 0)
				return (ptr);
			ptr = ptr->next;
		}
	}
	return (NULL);
}
