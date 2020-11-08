/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:41:54 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 02:00:43 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sh21.h"

void			fill(t_env_vars *var, char **env)
{
	while (env[(*var).i][(*var).j] != '=' && (env[(*var).i][(*var).j]))
	{
		(*var).name[(*var).j] = env[(*var).i][(*var).j];
		(*var).j++;
	}
	(*var).j++;
	while (env[(*var).i][(*var).j] != '\0')
	{
		(*var).value[(*var).c] = env[(*var).i][(*var).j];
		(*var).c++;
		(*var).j++;
	}
}

t_env			*env_lst_adder(t_env **old, t_env *new)
{
	t_env		*head;

	head = *old;
	if (!head)
	{
		*old = new;
		return (new);
	}
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
		new = NULL;
		return (*old);
	}
}

t_env			*env_create(char *name, char *value)
{
	t_env		*list;

	if (!(list = (t_env *)(ft_memalloc(sizeof(t_env)))))
		return (NULL);
	if (name)
	{
		list->name = ft_strdup(name);
		if (value)
			list->value = ft_strdup(value);
	}
	return (list);
}

void			env_to_list(t_env **lst, char **env)
{
	t_env_vars	var;

	var.i = 0;
	ft_bzero((void *)var.name, 2000);
	ft_bzero((void *)var.value, 5000);
	if (!env)
		*lst = env_create(var.name, var.value);
	else
	{
		while (env[var.i])
		{
			var.j = 0;
			var.c = 0;
			fill(&var, env);
			var.new = env_create(var.name, var.value);
			ft_strclr(var.name);
			ft_strclr(var.value);
			*lst = env_lst_adder(lst, var.new);
			var.i++;
		}
	}
}
