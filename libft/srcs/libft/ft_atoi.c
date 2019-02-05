/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:42:15 by pchadeni          #+#    #+#             */
/*   Updated: 2017/11/08 16:34:59 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			res;
	int			neg;
	int			i;
	const char	*tmp;

	res = 0;
	neg = 1;
	i = 0;
	tmp = str;
	while (tmp[i] == ' ' || (tmp[i] >= 9 && tmp[i] <= 13))
		i++;
	if (tmp[i] == '-')
		neg = -1;
	if (tmp[i] == '-' || tmp[i] == '+')
		i++;
	while (tmp[i] >= '0' && tmp[i] <= '9')
	{
		res = res * 10 + (tmp[i] - '0');
		i++;
	}
	return (res * neg);
}
