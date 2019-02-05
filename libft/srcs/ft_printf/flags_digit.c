/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:11:31 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/09 13:31:02 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*display_hex_oct(t_struct *s, char *str, char c, int pos)
{
	char	buf[4];
	char	*res;

	ft_bzero(buf, 4);
	if (s->flags & F_HASHTAG && (c == 'o' || c == 'O') && pos)
		put_in_buffer(buf, '0');
	if ((s->flags & F_HASHTAG && (c == 'x' || c == 'X') && pos) || c == 'p')
	{
		put_in_buffer(buf, '0');
		(c == 'x' || c == 'p') ?
			put_in_buffer(buf, 'x') : put_in_buffer(buf, 'X');
	}
	if (!ft_strchr("bxXOouU", c))
	{
		(s->flags & F_PLUS && pos >= 0) ? put_in_buffer(buf, '+') : 0;
		(pos == -1) ? put_in_buffer(buf, '-') : 0;
		if ((s->flags & F_SPACE) && pos >= 0)
			put_in_buffer(buf, ' ');
	}
	if (buf[0] != '\0')
		res = ft_strjoin(buf, str);
	else
		return (ft_strdup(str));
	return (res);
}

char	*check_precision_digit(t_struct *s, char *tmp, char c)
{
	int		len_tmp;
	char	*res;

	len_tmp = ft_strlen(tmp);
	if ((c == 'o' || c == 'O') && s->precision >= 0 &&
			s->flags & F_HASHTAG && tmp[0] != '0')
		len_tmp++;
	res = NULL;
	if (s->precision > len_tmp)
	{
		res = display_field(s->precision - len_tmp, '0');
		res = ft_strjoindel(res, tmp);
	}
	else if (!s->precision && tmp[0] == '0' &&
		(ft_strchr("xXp", c) || !(s->flags & F_HASHTAG)))
		res = ft_strdup("");
	else
		return (ft_strdup(tmp));
	return (res);
}

char	*dis_minus(t_struct *s, char *str, char *field)
{
	char	*last;

	if (!(s->flags & F_MINUS) && field && s->len_field > s->precision)
		last = ft_strjoin(field, str);
	else if ((s->flags & F_MINUS) && field && s->len_field > s->precision)
		last = ft_strjoin(str, field);
	else
		last = ft_strdup(str);
	ft_strdel(&str);
	ft_strdel(&field);
	return (last);
}

int		dis_len(t_struct *s, char *str, char c, int pos)
{
	int		len;
	int		len_fin;

	len = ft_strlen(str);
	len = (c == 'p' ||
		((s->flags & F_HASHTAG) && (c == 'x' || c == 'X') && pos))
		? len + 2 : len;
	len = ((s->flags & F_HASHTAG) && (c == 'o' || c == 'O') && pos) ?
		len + 1 : len;
	len = ((pos == -1 || (s->flags & F_PLUS)) &&
		(c == 'D' || c == 'd' || c == 'i')) ? len + 1 : len;
	len = ((!(s->flags & F_PLUS) && (s->flags & F_SPACE)) &&
		(c == 'D' || c == 'd' || c == 'i') && pos >= 0) ? len + 1 : len;
	len_fin = (s->precision != -1 && s->precision > len) ? s->precision : len;
	return (len_fin);
}

char	*dis_width_digit(t_struct *s, char *str, char c, int pos)
{
	int		len_fin;
	char	*tmp;
	char	*field;

	len_fin = dis_len(s, str, c, pos);
	if ((s->flags & F_ZERO) && len_fin < s->len_field)
	{
		field = display_field(s->len_field - len_fin, '0');
		field = ft_strjoindel(field, str);
		tmp = display_hex_oct(s, field, c, pos);
		ft_strdel(&field);
		s->flags += ~(F_HASHTAG & F_PLUS & F_SPACE);
		return (tmp);
	}
	tmp = display_hex_oct(s, str, c, pos);
	len_fin = ft_strlen(tmp);
	len_fin = (s->precision == -1 || s->precision < len_fin) ?
		len_fin : s->precision;
	if (len_fin < s->len_field)
	{
		field = display_field(s->len_field - len_fin, ' ');
		tmp = dis_minus(s, tmp, field);
	}
	return (tmp);
}
