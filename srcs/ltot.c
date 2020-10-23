/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 00:28:57 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/23 00:29:18 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		ft_rmpl(char **str, char *s, char *s2)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, s);
	free(tmp);
	tmp = *str;
	*str = ft_strjoin(*str, "=");
	free(tmp);
	tmp = *str;
	*str = ft_strjoin(*str, s2);
	free(tmp);
}

char		**ltot(t_env *env)
{
	t_env	*new;
	int		c;
	char	**str;

	new = env;
	c = 0;
	while (new)
	{
		c++;
		new = new->next;
	}
	if (!(str = (char **)ft_memalloc(sizeof(char *) * (c + 1))))
		return (NULL);
	ft_bzero((void*)str, c + 1);
	c = 0;
	while (env)
	{
		str[c] = ft_strnew(0);
		ft_rmpl(&str[c], env->name, env->value);
		c++;
		env = env->next;
	}
	return (str);
}
