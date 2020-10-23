/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:13:51 by afaragi           #+#    #+#             */
/*   Updated: 2020/10/22 23:31:39 by afaragi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
# include "../include/sh21.h"

# define BUFF_SIZE 1


typedef	struct		s_list
{
	char			*content;
	struct stat		st;
	size_t			content_size;
	char			*path;
	struct s_list	*next;
}					t_list;

void				ft_putnbr(int n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				ft_bzero(void *dst, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
size_t				ft_strlen(const char *s);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr (const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_whiteco(char const *s);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*fu)(char *));
char				*ft_strmap(char const *s, char (*fu)(char));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
void				ft_putchar(char c);
void				ft_putendl(char const *s);
void				ft_putstr(char const *s);
char				**ft_strsplit(char const *s, char c);
int					ft_strequ(char const *s1, char const *s2);
void				ft_putchar_fd(char c, int fd);
int					ft_strnequ(char const *s1, char const *s2, size_t e);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_striteri(char *s, void (*fu)(unsigned int, char *));
char				*ft_strmapi(char const *s, char (*fu)(unsigned int, char));
char				*ft_itoa(int nb);
void				ft_cremplire(char *e, char const *s, char c);
int					ft_countw(char const *s, char c);
int					ft_ctc(char const *s, char c);
int					ft_count_size(char const *s);
void				ft_remplir(char *dest, char const *src, int start, int end);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*fu)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*fu)(t_list *elem));
char				*ft_isspace(const char *str);
int					ft_intcount(int n);
t_list				*ft_lstpush(t_list **alst, t_list *new);
void				ft_deletlist(t_list **alst,
						void (*del)(void *, size_t, void *));
void				ft_deletone(t_list **alst,
						void (*del)(void *, size_t, void *));
char			**ft_strwhitesplit(char const *s);
void			ft_whiteremplire(char *r, char const *s);
int					ft_whitec(char const *s);
int					get_next_line(const int fd, char **line);
char				*ft_strdup_from_to(const char *s, int start, int end);
void				ft_move_replace(char *str);
void				delkill(char **paths);
#endif
