/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:12:39 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/27 11:39:11 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*exit_printf(t_struct *s)
{
	s->exit = 1;
	return (NULL);
}

char	*null_res(char *res)
{
	ft_strdel(&res);
	return (NULL);
}
