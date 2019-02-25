/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_addr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:34:27 by pchadeni          #+#    #+#             */
/*   Updated: 2019/02/25 16:39:08 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

void	write_addr(char res[])
{
	int	i;

	i = 63;
	while (res[i] != '\0')
		i--;
	i++;
	if (res[i])
		write(1, &res[i], 64 - i);
}

void	handle_addr(size_t value, int base)
{
	int		i;
	char	res[65];
	char	labase[16];

	labase = ft_strcpy(labase, "0123456789ABCDEF");
	if (value == 0)
	{
		ft_putchar('0');
		return ;
	}
	res[64] = '\0';
	ft_bzero(res, 64);
	i = 63;
	while (value != 0)
	{
		res[i] = labase[value % base];
		value /= base;
		i--;
	}
	write_addr(res);
	return ;
}
