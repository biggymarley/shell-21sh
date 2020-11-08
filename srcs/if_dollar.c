/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 04:47:35 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 04:58:31 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

int			check_for_syntax(char *tmp, t_env *penv)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '$' && penv != NULL
			&& (tmp[i + 1] == '\0' || tmp[i + 1] == ' '))
		{
			ft_putstr("Syntax Error.\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

int			if_errors(t_vars *vars)
{
	if ((*vars).penv == NULL)
	{
		ft_putalnum_fd((*vars).envs[(*vars).i], 2);
		ft_putstr_fd(": Undefined variable.\n", 2);
		delkill((*vars).envs);
		return (-1);
	}
	return (1);
}

int			replace_value(char **str, char *vars, char *value)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = *str;
	*str = ft_strjoin(*str, value);
	free(tmp);
	while (vars[i] && (ft_isalnum(vars[i]) || vars[i] == '_'))
		i++;
	tmp = *str;
	*str = ft_strjoin(*str, &vars[i]);
	free(tmp);
	return (1);
}

int			ft_checker(char **str, t_env *env)
{
	t_vars vars;

	vars.i = 0;
	if (!(vars.tmp = ft_strchr(*str, '$')))
		return (1);
	if (vars.tmp)
	{
		vars.envs = ft_strsplit(vars.tmp, '$');
		ft_strclr(vars.tmp);
		while (vars.envs[vars.i])
		{
			vars.penv = env_dollar_finder(env, vars.envs[vars.i]);
			if (if_errors(&vars) == -1)
				return (-1);
			else
				replace_value(str, vars.envs[vars.i], vars.penv->value);
			vars.i++;
		}
		delkill(vars.envs);
		return (1);
	}
	else
		return (0);
}

int			ft_check_dollars(char **str, t_env *env)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_checker(&str[i], env) == -1)
			return (0);
		i++;
	}
	return (1);
}
