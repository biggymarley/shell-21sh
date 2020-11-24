/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 23:28:50 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/24 01:32:57 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

t_env			*search_env(t_env *env, char *name)
{
	t_env		*ptr;
	int			i;

	i = 0;
	ptr = env;
	if (ptr)
	{
		while (ptr && ptr->name)
		{
			if (ft_strcmp(ptr->name, name) == 0)
				return (ptr);
			ptr = ptr->next;
		}
	}
	return (NULL);
}

int				check(t_env **lst, char *str)
{
	if (ft_strchr(str, '/'))
		if (access(str, F_OK) == 0)
			return (1);
	*lst = search_env(*lst, "PATH");
	return (0);
}

int				error_cmd(char *cmd, char *str)
{
	if (!(ft_strncmp(&cmd[0], "./", ft_strlen("./"))))
	{
		if (access(cmd, F_OK) != 0)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": no such file or directory.\n", 2);
			return (0);
		}
	}
	else if (!str)
	{
		ft_putstr_fd("\aSHELL: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	return (1);
}

void			join_path(t_ff *ff, char *cmd)
{
	(*ff).tmp = (*ff).paths[(*ff).i];
	(*ff).paths[(*ff).i] = ft_strjoin((*ff).paths[(*ff).i], "/");
	free((*ff).tmp);
	(*ff).tmp = (*ff).paths[(*ff).i];
	(*ff).paths[(*ff).i] = ft_strjoin((*ff).paths[(*ff).i], cmd);
	free((*ff).tmp);
}

char			**found_func(t_env *lst, char *cmd, char **str)
{
	t_ff ff;

	ff.i = -1;
	if (check(&lst, str[0]) == 1)
		return (str);
	if (lst == NULL)
		return (NULL);
	ff.paths = ft_strsplit(lst->value, ':');
	while (ff.paths[++ff.i])
	{
		join_path(&ff, cmd);
		if (access(ff.paths[ff.i], F_OK) == 0)
			break ;
	}
	if (!(error_cmd(str[0], ff.paths[ff.i])))
		return (NULL);
	ft_strdel(&str[0]);
	str[0] = ft_strdup(ff.paths[ff.i]);
	delkill(ff.paths);
	return (str);
}
