/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 10:59:23 by pchadeni          #+#    #+#             */
/*   Updated: 2019/02/20 10:43:47 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

uint8_t	ft_expten(int n)
{
	if (n >= 1000000000)
		return (10);
	else if (n >= 100000000)
		return (9);
	else if (n >= 10000000)
		return (8);
	else if (n >= 1000000)
		return (7);
	else if (n >= 100000)
		return (6);
	else if (n >= 10000)
		return (5);
	else if (n >= 1000)
		return (4);
	else if (n >= 100)
		return (3);
	else if (n >= 10)
		return (2);
	else if (n > 0)
		return (1);
	return (0);
}

int		ft_pow(int n, int pow)
{
	if (pow < 0)
		return (0);
	if (pow == 0)
		return (1);
	if (pow > 1)
		return (n * ft_pow(n, pow - 1));
	return (n);
}

unsigned int		ft_sqrt(int nb)
{
	int	i;
	int	res;
	int	end;
	int	mid;

	i = 1;
	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	end = nb;
	while (i <= end)
	{
		mid = (i + end) / 2;
		if (mid * mid == nb)
			return mid;
		if (mid * mid < nb)
		{
			i = mid + 1;
			res = mid;
		}
		else
			end = mid-1;
	}
	return (res);
}
