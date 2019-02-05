/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_flags_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:11:31 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/04 15:43:29 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*display_field(int len_tmp, char to_print)
{
	char	buf[len_tmp + 1];
	int		i;
	char	*tmp;

	i = 0;
	while (i < len_tmp)
	{
		buf[i] = to_print;
		i++;
	}
	buf[i] = '\0';
	tmp = ft_strdup(buf);
	return (tmp);
}

char	*display_sp(t_struct *s, int len_tmp)
{
	char	to_print;
	char	*tmp;

	to_print = ' ';
	if ((s->flags & F_ZERO) && !(s->flags & F_MINUS))
		to_print = '0';
	tmp = NULL;
	if (s->len_field > len_tmp)
		tmp = display_field(s->len_field - len_tmp, to_print);
	return (tmp);
}

char	*check_precision_str(t_struct *s, char *tmp)
{
	char	*res;
	int		len;

	len = ft_strlen(tmp);
	if (s->precision != -1 && s->precision < len)
	{
		res = ft_strndup(tmp, s->precision);
		ft_strdel(&tmp);
		return (res);
	}
	else
		return (tmp);
}
