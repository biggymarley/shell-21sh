/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 04:40:42 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 03:44:44 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			if_i_found_it(t_env *previous, t_env *ptr, t_env **env, char *str)
{
	if (ft_strcmp(ptr->name, str) == 0)
	{
		if (previous)
			previous->next = ptr->next;
		else
			*env = ptr->next;
		ft_one_envdel(&ptr, del);
		return (-1);
	}
	return (1);
}

void		delete_env_var(t_env **env, char **str)
{
	t_env	*ptr;
	t_env	*previous;
	int		i;

	i = 1;
	if (!str[1])
		ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
	else
	{
		while (str[i])
		{
			ptr = *env;
			previous = NULL;
			while (ptr && ptr->name)
			{
				if (if_i_found_it(previous, ptr, env, str[i]) == -1)
					break ;
				previous = ptr;
				ptr = ptr->next;
			}
			i++;
		}
	}
}
