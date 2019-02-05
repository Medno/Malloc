/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:10:04 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/07 13:02:02 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_struct(t_struct *s)
{
	s->flags = 0;
	s->precision = -1;
	s->len_field = 0;
	s->modif = 0;
	s->len = 0;
	s->exit = 0;
	s->eoc = 0;
	s->str = ft_strdup("");
}

void	reinit_struct(t_struct *s)
{
	s->flags = 0;
	s->precision = -1;
	s->len_field = 0;
	s->modif = 0;
}

void	put_in_buffer(char buf[], char c)
{
	int	len;

	len = ft_strlen(buf);
	buf[len] = c;
}
