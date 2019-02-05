/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_uni.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 11:46:10 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/07 11:52:15 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	first_st(wchar_t c, char uni[4])
{
	uni[0] = c;
	return (1);
}

static int	second_st(wchar_t c, char uni[4])
{
	uni[0] = (c >> 6) | 0xC0;
	uni[1] = (c & 0x3F) | 0x80;
	return (2);
}

static int	third_st(wchar_t c, char uni[4])
{
	uni[0] = (c >> 12) | 0xE0;
	uni[1] = ((c >> 6) & 0x3F) | 0x80;
	uni[2] = (c & 0x3F) | 0x80;
	return (3);
}

static int	forth_st(wchar_t c, char uni[4])
{
	uni[0] = (c >> 18) | 0xF0;
	uni[1] = ((c >> 12) & 0x3F) | 0x80;
	uni[2] = ((c >> 6) & 0x3F) | 0x80;
	uni[3] = (c & 0x3F) | 0x80;
	return (4);
}

int			check_chart(wchar_t c, char uni[4])
{
	if ((c >= 0xD800 && c <= 0xDFFF) || c > 0x10FFFF || c < 0 || c == 256)
		return (-1);
	if (c <= 127)
		return (first_st(c, uni));
	else if (c <= 0x7FF)
		return (second_st(c, uni));
	else if (c <= 0xFFFF)
		return (third_st(c, uni));
	else if (c <= 0x10FFFF)
		return (forth_st(c, uni));
	return (-1);
}
