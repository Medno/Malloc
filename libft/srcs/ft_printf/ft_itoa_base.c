/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:17:49 by pchadeni          #+#    #+#             */
/*   Updated: 2018/05/09 10:18:20 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	ft_absi(intmax_t n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int				nb_char(intmax_t n, int base)
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

char			*ft_itoa_base(intmax_t value, int base)
{
	int		nb_c;
	char	*res;
	char	labase[17];

	put_in_base(labase);
	nb_c = nb_char(value, base);
	if (value == 0)
		return (ft_strdup("0"));
	if (!(res = (char *)malloc(sizeof(char) * nb_c + 1)))
		return (NULL);
	res[nb_c] = '\0';
	nb_c--;
	while (value != 0)
	{
		res[nb_c] = labase[ft_absi(value % base)];
		value /= base;
		nb_c--;
	}
	return (res);
}
