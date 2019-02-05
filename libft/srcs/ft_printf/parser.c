/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:21:20 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/07 13:01:51 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		put_in_struct(const char *f, t_struct *s, char *tmp, int len_tmp)
{
	char buf[s->eoc + 1];

	ft_bzero(buf, s->eoc + 1);
	ft_strncat(buf, f, s->eoc);
	s->str = ft_strjoinzero(s->str, buf, s->len, s->eoc);
	s->len += s->eoc;
	s->str = ft_strjoinzero(s->str, tmp, s->len, len_tmp);
	s->len += len_tmp;
}

char		*display_digit(t_struct *s, va_list ap, char conv, int *len_tmp)
{
	char *tmp;

	if (conv == 'd' || conv == 'i' || conv == 'D')
		tmp = conv_di(s, ap, conv);
	else
		tmp = conv_ouxx(s, ap, conv);
	*len_tmp = ft_strlen(tmp);
	return (tmp);
}

t_struct	*check_conversion(const char *f, int *i, t_struct *s, va_list ap)
{
	char	*tmp;
	int		len_tmp;

	len_tmp = 0;
	if (f[*i] == 'S' || (f[*i] == 's' && s->modif == F_L))
		tmp = conv_majs(s, ap, &len_tmp);
	else if (f[*i] == 's')
		tmp = get_str(s, ap, &len_tmp);
	else if (digit_conv(f[*i]))
		tmp = display_digit(s, ap, f[*i], &len_tmp);
	else if (f[*i] == 'p')
		tmp = conv_p(s, ap, &len_tmp);
	else if (f[*i] == 'C' || (f[*i] == 'c' && s->modif == F_L))
		tmp = conv_majc(s, ap, &len_tmp);
	else if (f[*i] == 'c')
		tmp = get_char_va(s, ap, &len_tmp, -1);
	else
		tmp = get_char_va(s, ap, &len_tmp, f[*i]);
	if (tmp && !s->exit)
	{
		put_in_struct(f, s, tmp, len_tmp);
		ft_strdel(&tmp);
	}
	return (s);
}

void		treat_format(const char *format, int *i, t_struct *s, va_list ap)
{
	(*i)++;
	while (format[*i] && (is_flag(format[*i]) || ft_isdigit(format[*i])))
	{
		s = check_flags(format, i, s);
		s = (format[*i] != '0') ? field_preci(format, i, s, ap) : s;
		(*i)++;
	}
	s = last_check(s, format[*i]);
	if (format[*i])
	{
		s->modif = (ft_strchr("DUO", format[*i])) ? F_L : s->modif;
		s = check_conversion(format, i, s, ap);
	}
	else
		return ;
	(*i)++;
}

void		parser(const char *format, va_list ap, t_struct *s)
{
	int	i;

	i = 0;
	while (format[i] && !s->exit)
	{
		if (format[i] && format[i] == '%' && format[i + 1])
		{
			s->eoc = i;
			treat_format(format, &i, s, ap);
			format += i;
			i = 0;
			reinit_struct(s);
		}
		else if (format[i] && format[i] == '%' && !format[i + 1])
			break ;
		else
			i++;
	}
	s->str = ft_strjoinzero(s->str, (char *)format, s->len, i);
	s->len += i;
}
