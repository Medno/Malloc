/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_majs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 11:29:31 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/07 11:48:24 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*display_uni(t_struct *s, wchar_t tmp)
{
	char	uni[5];
	char	*tmp_s;

	ft_bzero(uni, 5);
	tmp_s = NULL;
	if (check_chart(tmp, uni) == -1)
		return (exit_printf(s));
	if (!uni[0])
		tmp_s = ft_put_in_str(tmp_s, '\0');
	else
		tmp_s = ft_strdup(uni);
	return (tmp_s);
}

char		*conv_majc(t_struct *s, va_list ap, int *len_tmp)
{
	char	*tmp;
	wchar_t	get;

	get = va_arg(ap, wchar_t);
	tmp = NULL;
	tmp = display_uni(s, get);
	if (tmp)
		tmp = display_char(s, tmp, len_tmp);
	return (tmp);
}

static char	*cat_each_uni(t_struct *s, wchar_t *get)
{
	char	*res;
	char	*tmp;
	int		preci;
	int		len_tmp;

	res = get ? ft_strdup("") : NULL;
	preci = s->precision;
	while (get && *get && !s->exit && preci)
	{
		tmp = display_uni(s, *get);
		if (!tmp)
			return (null_res(res));
		len_tmp = ft_strlen(tmp);
		if (preci > 0 && len_tmp > preci)
		{
			ft_strdel(&tmp);
			break ;
		}
		else if (preci > 0)
			preci -= len_tmp;
		res = ft_strjoindel(res, tmp);
		ft_strdel(&tmp);
		get++;
	}
	return (res);
}

char		*conv_majs(t_struct *s, va_list ap, int *len)
{
	char	*res;
	wchar_t	*get;
	char	*tmp;

	get = va_arg(ap, wchar_t *);
	tmp = cat_each_uni(s, get);
	if (!tmp)
		return (NULL);
	if (s->exit)
		return (null_res(tmp));
	res = display_str(s, tmp, len);
	ft_strdel(&tmp);
	return (res);
}
