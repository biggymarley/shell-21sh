/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:26:51 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/22 05:33:19 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
#define SH21_H
#define READ_F_F 1	   // < no rightfd done 
#define RED_TRUNC 2		   // > no rightfd 
#define RED_APPND 4		   // >> no rightfd
#define HERDOC 8		   // << no rightfd -
#define HERSTR 16		   // <<< norightfd
#define SWAP_LFD_TRFD 32   // >& both ok , '-' 1>&2- 
#define READ_FCUSFD 64	   // <&  both 
#define CLOSE_RFD 128	   // -
#define RED_STDOUT_ERR 256 // &> err stdout to file no lftfd

#include "../libft/libft.h"

typedef struct	s_env
{
	char        *name;
	char        *value;
	struct s_env *next;
}               t_env;

typedef struct  s_env_vars
{
	t_env       *new;
	char        name[2000];
	char        value[5000];
	int         i;
	int         j;
	int         c;
}				t_env_vars;

typedef struct      s_red
{
    unsigned int    lfd;
    unsigned int    rfd;
    unsigned int    type;
    char            *file;
    struct s_red    *next;
}                   t_red;

typedef struct      s_cmd
{
    char            *cmd;
    struct s_cmd    *pipe;
    struct s_cmd    *sep;
    t_red           *red;
}                   t_cmd;

void                printer();
void                env_to_list(t_env **lst, char **env);
void                free_list(t_cmd **cmd_list);
void                errors(int op, t_cmd **cmd_list);
void                pipe_reader(char **str);
int                 pipe_parser(t_cmd **cmd_list, char **cmd, int i);
int                 sep_parser(t_cmd **cmd_list, char *cmd, int i, t_cmd **last_sep);
int                 single_cmd_parser(t_cmd **cmd_list, char *cmd, int i, int last_index);
t_cmd               *parser(char *cmd_line);
int                 red_parser(t_cmd **cmd_list);
int                 red_checker(char *line, int i, char red1, char red2);
int                 red_errors_checker(char *line, int i);
void                free_env(t_env **env);

#endif