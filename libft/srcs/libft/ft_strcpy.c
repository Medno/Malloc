/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:41:00 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 13:05:27 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int			i;
	const char	*tmp;

	i = 0;
	tmp = src;
	while (tmp[i])
	{
		dst[i] = tmp[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	const char	*tmp;
	size_t		i;
	size_t		temp;

	i = 0;
	tmp = src;
	temp = len;
	while (tmp[i] && temp > i)
	{
		dst[i] = tmp[i];
		i++;
	}
	if (i != len)
		while (i < len)
		{
			dst[i] = '\0';
			i++;
		}
	return (dst);
}
