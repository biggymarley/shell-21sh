/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 03:42:21 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 02:05:38 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void		ft_if_no_existe(t_env **env, char *envname)
{
	char	*newstr;
	char	**newenvadded;
	char	*tmp;

	newstr = getcwd(NULL, 0);
	tmp = newstr;
	newstr = ft_strjoin(envname, newstr);
	free(tmp);
	newenvadded = ft_strsplit(newstr, '@');
	ft_setenv(env, newenvadded);
	delkill(newenvadded);
	free(newstr);
}

void		cd_cases(t_cd *cd, char *str, t_env **env)
{
	if (!str)
		(*cd).ptr = search_env(*env, "HOME");
	else if (ft_strcmp(str, "-") == 0)
	{
		(*cd).ptr = search_env(*env, "OLDPWD");
		if ((*cd).ptr)
			ft_putendl((*cd).ptr->value);
	}
	else if (ft_strcmp(str, "~") == 0)
	{
		(*cd).ptr = search_env(*env, "HOME");
		if ((*cd).ptr)
			ft_putendl((*cd).ptr->value);
	}
}

int			if_no_directory(t_cd *cd, char *str)
{
	if (access((*cd).nwpwd, F_OK | X_OK) != 0)
	{
		ft_putstr_fd(": cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
		free((*cd).nwpwd);
		return (1);
	}
	return (0);
}

void		if_no_env(t_cd *cd, t_env **env, char *name, char *spli)
{
	char *tst;

	(*cd).ptr = search_env(*env, name);
	if (!(*cd).ptr)
		ft_if_no_existe(env, spli);
	else
	{
		if ((tst = getcwd(NULL, 0)) != NULL)
		{
			free((*cd).ptr->value);
			(*cd).ptr->value = ft_strdup(tst);
			free(tst);
		}
	}
}

void		ft_cd(char **str, t_env **env)
{
	t_cd	cd;

	cd.ptr = NULL;
	if (ft_strcmp(str[0], "cd") == 0)
	{
		cd_cases(&cd, str[1], env);
		if (cd.ptr)
			cd.nwpwd = ft_strdup(cd.ptr->value);
		else
			cd.nwpwd = ft_strdup(str[1]);
		if (if_no_directory(&cd, str[1]) == 1)
			return ;
		if_no_env(&cd, env, "OLDPWD", "NOTHING@OLDPWD@");
		chdir(cd.nwpwd);
		if_no_env(&cd, env, "PWD", "NOTHING@PWD@");
		free(cd.nwpwd);
		return ;
	}
	return ;
}
