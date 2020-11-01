/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 03:43:47 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/01 04:04:54 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			if_alpha_num(char *name)
{
	int		i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
			return (0);
		i++;
	}
	return (1);
}

int		counter(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			search_found_replace(t_env **env, char **str)
{
	t_env	*ptr;

	if ((ptr = search_env(*env, str[1])))
	{
		free(ptr->value);
		if (!str[2])
			ptr->value = ft_strnew(0);
		else
			ptr->value = ft_strdup(str[2]);
		return (1);
	}
	return (0);
}

int			errors_cases(int i, char *str, t_env **env)
{
	if (i > 3)
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return (0);
	}
	if (!str)
	{
		ft_env(*env);
		return (1);
	}
	return (-1);
}

int			ft_setenv(t_env **env, char **str)
{
	int		i;
	int		a;
	char	**nev;
	t_env	*new;

	i = counter(str);
	if ((a = errors_cases(i, str[1], env)) != -1)
		return (a);
	else if (!if_alpha_num(str[1]))
	{
		ft_putendl_fd("setenv: alphanumeric characters only.", 2);
		return (0);
	}
	else
	{
		if (search_found_replace(env, str))
			return (1);
		if (str[2])
			new = env_create(str[1], str[2]);
		else
			new = env_create(str[1], "\0");
		*env = env_lst_adder(env, new);
	}
	return (1);
}