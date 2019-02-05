/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:22:36 by pchadeni          #+#    #+#             */
/*   Updated: 2017/11/09 19:10:57 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_nb(int n)
{
	int	res;

	res = (n <= 0) ? 1 : 0;
	while (n != 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}

char			*ft_itoa(int n)
{
	char	*tmp;
	int		size;

	size = nb_nb(n);
	if ((tmp = ft_strnew(size)))
	{
		if (n < 0)
			tmp[0] = '-';
		tmp[size] = '\0';
		if (n == 0)
			tmp[0] = '0';
		while (n != 0)
		{
			tmp[size - 1] = ft_abs(ft_abs(n % 10)) + '0';
			n /= 10;
			size--;
		}
		return (tmp);
	}
	return (NULL);
}
