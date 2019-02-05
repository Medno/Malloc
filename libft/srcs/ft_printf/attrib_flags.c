/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attrib_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 09:45:16 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/07 10:55:43 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		check_field(const char *format, int *i)
{
	int	field;
	int	expten;

	field = 0;
	expten = 1;
	while (format[*i] && ft_isdigit(format[*i]))
	{
		field = format[*i] - '0' + expten * field;
		expten *= 10;
		(*i)++;
	}
	(*i)--;
	return (field);
}

static t_struct	*check_lenmod(const char *f, int *i, t_struct *s)
{
	if (f[*i] && f[*i] == 'h' && s->modif < F_H)
		s->modif = (f[*i + 1] && f[*i + 1] == 'h' && (*i)++) ? F_HH : F_H;
	if (f[*i] && f[*i] == 'l' && s->modif < F_LL)
		s->modif = (f[*i + 1] && f[*i + 1] == 'l' && (*i)++) ? F_LL : F_L;
	if (f[*i] && f[*i] == 'j' && s->modif < F_J)
		s->modif = F_J;
	if (f[*i] && f[*i] == 'z' && s->modif < F_J)
		s->modif = F_Z;
	return (s);
}

static int		flag_star(t_struct *s, va_list ap, int preci)
{
	int	res;

	res = va_arg(ap, int);
	if (res < 0 && preci)
		return (-1);
	if (res < 0 && !preci)
	{
		s->flags |= F_MINUS;
		res = -res;
	}
	return (res);
}

t_struct		*field_preci(const char *f, int *i, t_struct *s, va_list ap)
{
	if (f[*i] && ft_isdigit(f[*i]))
		s->len_field = check_field(f, i);
	else if (f[*i] && f[*i] == '*')
		s->len_field = flag_star(s, ap, 0);
	if (f[*i] && f[*i] == '.')
	{
		(*i)++;
		s->precision = (f[*i] && f[*i] == '*') ?
			flag_star(s, ap, 1) : check_field(f, i);
	}
	if (f[*i] && ft_strchr("hljz", f[*i]))
		s = check_lenmod(f, i, s);
	return (s);
}
