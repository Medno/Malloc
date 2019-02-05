/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:35:52 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 13:04:27 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j] && n > 0)
	{
		s1[i] = s2[j];
		i++;
		j++;
		n--;
	}
	s1[i] = '\0';
	return (s1);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		len;

	i = 0;
	if (size == 0)
		return (ft_strlen(dst));
	while (dst[i] && i < size)
		i++;
	len = i;
	while (src[i - len] && size - 1 > i)
	{
		dst[i] = src[i - len];
		i++;
	}
	while (i < size)
	{
		dst[i] = '\0';
		i++;
	}
	return (len + ft_strlen(src));
}
