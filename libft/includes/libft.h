/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:10:25 by pchadeni          #+#    #+#             */
/*   Updated: 2019/01/17 18:18:00 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "ft_printf.h"
# define BOLD "\033[1m"
# define BLACK "\033[22;30m"
# define RED "\033[22;31m"
# define GREEN "\033[22;32m"
# define BROWN "\033[22;33m"
# define BLUE "\033[22;34m"
# define MAGENTA "\033[22;35m"
# define CYAN "\033[22;36m"
# define GRAY "\033[22;37m"
# define DARK_GRAY "\033[01;30m"
# define YELLOW "\033[33;20m"
# define LIGHT_RED "\033[01;31m"
# define LIGHT_GREEN "\033[01;32m"
# define LIGHT_BLUE "\033[01;34m"
# define LIGHT_MAGENTA "\033[01;35m"
# define LIGHT_CYAN "\033[01;36m"
# define WHITE "\033[01;37m"
# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_PINK "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_GRAY "\033[47m"
# define BUFF_SIZE 1000

typedef struct stat	t_stat;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_gnl
{
	int		fd;
	char	value[BUFF_SIZE + 1];
}				t_gnl;

typedef struct	s_point
{
	int	x;
	int y;
}				t_point;

int				get_next_line(const int fd, char **line);

char			**ft_strsplit(char const *s, char c);
char			**ft_splitwsp(char *str);

char			*ft_getopt(char **cmd, int *i);
char			*ft_itoa(int n);
char			*ft_onejoinf(char *news, char *old);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strlchr(const char *s, int c);
char			*ft_strfchr(char *str, char c);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t len);
char			*ft_strgap(char *str, char delim, int pos);
char			*ft_strlgap(char *str, char delim, int pos);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoindel(char *s1, char *s2);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strnew(size_t size);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack, const char *needle, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
char			*ft_stolower(char *str);

char			ft_lastchar(char *str);
unsigned int	ft_squared_vector_distance(t_point a, t_point b);

int				ft_atoi(const char *str);
int				ft_abs(int n);
int				ft_checkopt(char *p, char *str, int nb_opt);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_nbchar(char *str, char c);
int				ft_nbwords(char *str);
int				ft_pow(int n, int pow);
unsigned int				ft_sqrt(int nb);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_tolower(int c);
int				ft_toupper(int c);

size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s1);

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstclean(void *str, size_t size);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstsplit(char const *s, char c);
t_list			*ft_lsttail(t_list *lst);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstaddlast(t_list **list, t_list *add);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_lstindel(t_list **first, t_list *del);

uint8_t			ft_expten(int n);
uint8_t			ft_iswsp(char c);
uint8_t			ft_isdir(t_stat sb);
uint8_t			ft_isdot(char *path);
uint8_t			ft_isexe(t_stat stat);
uint8_t			ft_islink(t_stat stat);

void			*ft_memalloc(size_t size);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memalloc_uint(size_t size);

void			ft_bzero(void *s, size_t n);
void			ft_foreachint(int *tab, int length, void (*f)(int));
void			ft_memdel(void **ap);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putsgap(char *str, char n, int i);
void			ft_puttab(char **tab);
void			ft_putcolor(char *str, char *color);
void			ft_putformat(char *str, char *color, char *background);
void			ft_putnstr(const char *str, size_t len);
char			*ft_put_in_str(char *str, char c);
void			ft_strclr(char *s);
void			ft_strdel(char **as);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));

char			**ft_tabdup(char **tab);
void			ft_puttab(char **tab);
void			ft_tabdel(char **tab);
void			ft_del_array(void **array);

t_point		set_point(int x, int y);
char      *ft_strdup_count(const char *s1, const char searched, int *count);

#endif
