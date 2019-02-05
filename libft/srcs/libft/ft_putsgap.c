/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsgap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 10:48:31 by pchadeni          #+#    #+#             */
/*   Updated: 2017/12/21 15:22:01 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putbstr(char *str, size_t start, size_t end)
{
	if (start > end || end >= ft_strlen(str))
		return ;
	while (start <= end && str[start])
	{
		ft_putchar(str[start]);
		start++;
	}
}

void		ft_putsgap(char *str, char n, int i)
{
	int	count;
	int	start;
	int	end;

	count = 0;
	start = 0;
	end = 0;
	while (str[end] != '\0')
	{
		if (str[end] == n)
		{
			count++;
			if (count >= i && str[end - 1])
			{
				ft_putbstr(str, start, end - 1);
				return ;
			}
			if (str[end + 1])
				start = end + 1;
		}
		end++;
	}
	ft_putbstr(str, start, end - 1);
}
