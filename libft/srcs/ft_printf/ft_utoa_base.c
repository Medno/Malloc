/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:18:31 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/09 10:18:58 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		nb_char_u(uintmax_t n, int base)
{
	int	compt;

	compt = 0;
	while (n != 0)
	{
		compt++;
		n /= base;
	}
	return (compt);
}

void	put_in_base(char base[])
{
	base[0] = '0';
	base[1] = '1';
	base[2] = '2';
	base[3] = '3';
	base[4] = '4';
	base[5] = '5';
	base[6] = '6';
	base[7] = '7';
	base[8] = '8';
	base[9] = '9';
	base[10] = 'A';
	base[11] = 'B';
	base[12] = 'C';
	base[13] = 'D';
	base[14] = 'E';
	base[15] = 'F';
	base[16] = '\0';
}

char	*ft_utoa_base(uintmax_t value, int base)
{
	int		nb_c;
	char	*res;
	char	labase[17];

	put_in_base(labase);
	nb_c = nb_char_u(value, base);
	if (value == 0)
		return (ft_strdup("0"));
	if (!(res = (char *)malloc(sizeof(char) * nb_c + 1)))
		return (NULL);
	res[nb_c] = '\0';
	nb_c--;
	while (value != 0)
	{
		res[nb_c] = labase[value % base];
		value /= base;
		nb_c--;
	}
	return (res);
}
