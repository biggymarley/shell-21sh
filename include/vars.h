/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 23:07:18 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/07 23:48:13 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H
# include "sh21.h"

typedef struct		s_alias
{
	int				i;
	int				f;
	char			*file;
	char			*tmp;
	char			*value;
	char			**cmd;
	char			**cc;
}					t_alias;

typedef struct		s_alias2
{
	int				f;
	char			*file;
	char			*tmp;
	char			*value;
	char			**cmd;
	char			**cc;
}					t_alias2;

typedef struct		s_alias3
{
	int				i;
	int				f;
	char			*file;
	char			*tmp;
}					t_alias3;

typedef struct		s_dupexe
{
	int				built_cmd;
	char			**nev;
	int				fd[2];
	int				ex;
}					t_dupexe;

typedef struct		s_ff
{
	char			**paths;
	char			*tmp;
	int				i;
}					t_ff;

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_env_vars
{
	t_env			*new;
	char			name[2000];
	char			value[5000];
	int				i;
	int				j;
	int				c;
}					t_env_vars;

typedef struct		s_red
{
	unsigned int	lfd;
	unsigned int	rfd;
	unsigned int	type;
	char			*file;
	struct s_red	*next;
}					t_red;

typedef struct		s_cmd
{
	char			*cmd;
	struct s_cmd	*pipe;
	struct s_cmd	*sep;
	t_red			*red;
}					t_cmd;

typedef	struct		s_cd
{
	char			*nwpwd;
	char			*value;
	char			*newstr;
	char			*tmp;
	char			**newenvadded;
	t_env			*ptr;
}					t_cd;

typedef struct		s_parser
{
	int				i;
	int				li;
	t_cmd			*cmd_list;
	t_cmd			*head;
	t_cmd			*last_sep;
	char			*ptr;
}					t_parser;

typedef struct		s_core
{
	char			*buff;
	t_cmd			*cmd_line;
	t_cmd			**ptr;
	char			*str;
}					t_core;

typedef	struct		s_home
{
	char			*user;
	char			*value;
	char			*ptr;
	t_env			*penv;
}					t_home;

typedef	struct		s_vars
{
	int				i;
	char			*tmp;
	char			*ptr;
	char			**envs;
	t_env			*penv;
}					t_vars;

typedef	struct		s_join
{
	int				i;
	int				j;
	int				a;
	char			*t;
}					t_join;
#endif
