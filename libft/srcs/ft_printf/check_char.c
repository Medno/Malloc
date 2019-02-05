/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:21:20 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/09 13:29:35 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		digit_conv(char c)
{
	if (ft_strchr("bdDoOuUixX", c))
		return (1);
	return (0);
}

int		is_flag(char c)
{
	if (ft_strchr("*#0- +.hljz", c))
		return (1);
	return (0);
}

int		is_convert(char c)
{
	if (ft_strchr("b%sSpdDioOuUxXcC", c))
		return (1);
	return (0);
}
