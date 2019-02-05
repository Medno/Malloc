/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 10:51:09 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/11 18:51:34 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lookfor(int fd, t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (((t_gnl *)tmp->content)->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static int		backslash_n(const int fd, char **str, char buf[], t_list **stat)
{
	int		size;
	char	*back;
	char	*bef;
	t_gnl	new;

	back = ft_strchr(buf, '\n');
	if (!(back && *back))
		return (0);
	back++;
	size = ft_strlen(buf) - ft_strlen(back) - 1;
	bef = (size < 0) ? ft_strdup("") : ft_strsub(buf, 0, size);
	*str = (*str) ? ft_strjoindel(*str, bef) : ft_strdup(bef);
	ft_strdel(&bef);
	ft_bzero(new.value, BUFF_SIZE + 1);
	ft_strcpy(new.value, back);
	new.fd = fd;
	ft_lstadd(stat, ft_lstnew(&new, sizeof(t_gnl)));
	return (1);
}

static int		put_in_line(const int fd, char **str, t_list **stat)
{
	char	buf[BUFF_SIZE + 1];
	int		rd;

	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = '\0';
		if (backslash_n(fd, str, buf, stat))
			return (1);
		*str = (*str) ? ft_strjoindel(*str, buf) : ft_strdup(buf);
	}
	if (!*str && rd != -1)
		return (0);
	return (rd == -1) ? -1 : 1;
}

static int		clean_stat(t_list *tmp, char **str)
{
	int		i;
	char	*back;
	t_gnl	*new;

	new = tmp->content;
	back = ft_strchr(new->value, '\n');
	if (!back)
	{
		if (!ft_strlen(new->value))
			return (0);
		if (!(*str = ft_strdup(((t_gnl *)tmp->content)->value)))
			return (-1);
		ft_strclr(new->value);
		return (0);
	}
	i = ft_strlen(new->value) - ft_strlen(back);
	back++;
	*str = (i < 0) ? ft_strdup("") : ft_strsub(new->value, 0, i);
	back = ft_strdup(back);
	ft_strclr(new->value);
	ft_strcpy(new->value, back);
	ft_strdel(&back);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*stat = NULL;
	t_list			*tmp;
	int				line_ok;
	t_gnl			*gnl;

	if (fd < 0 || !line || fd > OPEN_MAX || BUFF_SIZE <= 0)
		return (-1);
	*line = NULL;
	line_ok = 0;
	gnl = NULL;
	tmp = lookfor(fd, stat);
	if (tmp)
		gnl = tmp->content;
	if (stat && tmp && gnl && (line_ok = clean_stat(tmp, line)) && line_ok)
		return ((line_ok == -2) ? 0 : line_ok);
	return (put_in_line(fd, line, &stat));
}
