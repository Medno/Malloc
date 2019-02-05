/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:33:59 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/07 09:46:00 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_struct		*check_flags(const char *format, int *i, t_struct *s)
{
	if (format[*i] == '#')
		s->flags |= F_HASHTAG;
	else if (format[*i] == '0')
		s->flags |= F_ZERO;
	else if (format[*i] == '-')
		s->flags |= F_MINUS;
	else if (format[*i] == ' ')
		s->flags |= F_SPACE;
	else if (format[*i] == '+')
		s->flags |= F_PLUS;
	return (s);
}

t_struct		*last_check(t_struct *s, char c)
{
	if ((s->flags & F_ZERO) && ((s->flags & F_MINUS) ||
			(s->precision != -1 && ft_strchr("dDioOuUixX", c))))
		s->flags ^= F_ZERO;
	if ((s->flags & F_PLUS) && (s->flags & F_SPACE))
		s->flags ^= F_SPACE;
	return (s);
}
