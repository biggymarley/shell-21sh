/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:26:51 by afaragi           #+#    #+#             */
/*   Updated: 2020/11/08 04:11:39 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# define READ_F_F 1
# define RED_TRUNC 2
# define RED_APPND 4
# define HERDOC 8
# define HERSTR 16
# define SWAP_LFD_TRFD 32
# define READ_FCUSFD 64
# define CLOSE_RFD 128
# define RED_STDOUT_ERR 256
# include "../libft/libft.h"
# include "vars.h"

void			printer();
void			env_to_list(t_env **lst, char **env);
void			free_list(t_cmd **cmd_list);
void			errors(int op, t_cmd **cmd_list);
void			pipe_reader(char **str);
int				pipe_parser(t_cmd **cmd_list, char **cmd, int i);
int				sep_parser(t_cmd **ct, char *cmd, int i, t_cmd **lp);
int				single_cmd_parser(t_cmd **ct, char *cmd, int i, int lx);
t_cmd			*parser(char **cmd_line);
int				red_parser(t_cmd **cmd_list);
int				red_checker(char *line, int i, char red1, char red2);
int				red_errors_checker(char *line, int i);
void			free_env(t_env **alst, void (*del)(void *, void *));
int				execute_cmd(t_cmd *cmd_list, t_env **env, int cmd_nbr);
char			**found_func(t_env *lst, char *cmd, char **str);
t_env			*search_env(t_env *env, char *name);
char			**ltot(t_env *env);
int				exec_red(t_red *red, int *f);
int				red_duper(t_red *red);
void			del(void *s, void *str);
void			del_cmd_lst(t_cmd **cmd);
void			read_herdoc(t_red *red);
int				cots_check(char **cmd_line, int balance);
void			rebase(char **cmd, char c, char b);
void			rebase_all(char **cmd);
int				ft_echo(char **str);
int				ft_setenv(t_env **env, char **str);
void			ft_cd(char **str, t_env **env);
void			ft_env(t_env *env);
void			execve_built(char *cmd, char **line, t_env **env, int cmdnbr);
t_env			*env_create(char *name, char *value);
t_env			*env_lst_adder(t_env **old, t_env *new);
void			execve_child(char *cmd, char **line, t_env **env, int cmdnbr);
int				if_bult(char **str);
void			delete_env_var(t_env **env, char **str);
void			ft_one_envdel(t_env **alst, void (*del)(void *, void *));
int				counter(char **str);
void			alias_parser(char **line);
int				alias_checker(char **line);
void			write_file(t_alias3 *alias, char **line);
int				alias_check(char **line);
char			**cmd_finder(t_env *env, char *cmd);
int				fdhandler(int cmd_nbr, int fr, int *fd, t_cmd *ct);
void			pr_writer(int balance);
void			cut_quotas(char **str, int *index, int balance);
void			rebase(char **cmd, char c, char b);
void			rebase_all(char **cmd);
int				balance_checker(char **str, int balance, int *i);
int				open_cots_checker(char **str, int balance);
void			joint(char **str, char *buff);
void			open_cots(char **str, int balance);
int				right_big_red_checker(char *line, int i, char red1, char red2);
int				left_big_red_checker(char *line, int i, int indice);
int				red_checker(char *line, int i, char red1, char red2);
int				red_errors_checker(char *line, int i);
int				fill_red_type(t_red **red_list, char *line, int i);
void			red_fdclose_add(t_cmd **line, unsigned int *type, int index);
int				right_fd_filler(t_red **red_list, t_cmd **line, int i);
int				index_placer(t_red *red_list);
void			strdup_clean(t_red **rt, t_cmd **line, int *index, int *i);
void			red_cleaner(t_red **red_list, int *start, t_cmd **line);
int				pipe_parser(t_cmd **cmd_list, char **cmd, int i);
int				sep_parser(t_cmd **ct, char *cmd, int i, t_cmd **lp);
void			free_red(t_red **red);
void			free_cmd_list(t_cmd **cmd_line);
int				if_home(char **str, t_env *env);
t_env			*env_dollar_finder(t_env *env, char *name);
int				ft_check_dollars(char **str, t_env *env);
int				ft_exit(char **str);
int				if_exit(char **cmd);
int				if_slash_or_dot(char *str);
#endif
