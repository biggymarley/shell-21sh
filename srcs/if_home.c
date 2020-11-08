/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 04:41:44 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 04:44:06 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			if_user_found(t_home *home)
{
	if (((*home).ptr = ft_strrchr((*home).value, '/')))
		ft_strclr(++(*home).ptr);
	(*home).ptr = (*home).value;
	(*home).value = ft_strjoin((*home).value, (*home).user);
	free((*home).ptr);
	if (access((*home).value, F_OK))
	{
		ft_putstr_fd("$: user not found: ", 2);
		ft_putendl_fd((*home).user, 2);
		free((*home).value);
		free((*home).user);
		return (-1);
	}
	free((*home).user);
	if (((*home).ptr = ft_strrchr((*home).value, '/')))
		ft_strclr(++(*home).ptr);
	return (0);
}

char		*get_username(char *str)
{
	char	*user;
	size_t	i;

	i = 0;
	if (ft_isalnum(*str))
	{
		user = ft_strdup(str);
		while (user[i] && ft_isalnum(user[i]))
			i++;
		ft_strclr(&user[i]);
		return (user);
	}
	return (NULL);
}

int			check_errors(t_home *home, char **str)
{
	if (!((*home).value = ft_strdup((*home).penv->value)))
	{
		ft_putstr_fd("HOME value not set\n", 2);
		free((*home).value);
		return (-1);
	}
	if (((*home).user = get_username(*str)))
	{
		if (if_user_found(home) == -1)
			return (-1);
	}
	return (0);
}

int			home_norm(char **str, t_env *env)
{
	t_home home;

	ft_move_replace(*str);
	home.penv = search_env(env, "HOME");
	if (home.penv)
	{
		if (check_errors(&home, str) == -1)
			return (-1);
		home.ptr = *str;
		*str = ft_strjoin(home.value, *str);
		free(home.ptr);
		free(home.value);
	}
	else
	{
		ft_putstr_fd("NO HOME SET\n", 2);
		return (-1);
	}
	return (0);
}

int			if_home(char **str, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "~") == 0)
		{
			free(str[i]);
			str[i] = ft_strdup("$HOME");
		}
		else if (str[i][0] == '~')
		{
			if (home_norm(&str[i], env) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}
