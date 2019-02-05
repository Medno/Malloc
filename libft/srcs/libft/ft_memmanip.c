/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmanip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:33:36 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 13:34:17 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)tmp[i] == (unsigned char)c)
			return (&tmp[i]);
		i++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;
	size_t		i;

	tmp_dst = dst;
	tmp_src = src;
	i = 0;
	while (n > i)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (tmp_dst);
}

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;
	size_t		i;

	i = 0;
	tmp_dst = dst;
	tmp_src = src;
	while (n > i)
	{
		tmp_dst[i] = tmp_src[i];
		if (tmp_src[i] == c)
			return (&tmp_dst[i + 1]);
		i++;
	}
	return (NULL);
}

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*tmp_s1;
	const unsigned char	*tmp_s2;
	size_t				i;

	i = 0;
	tmp_s1 = s1;
	tmp_s2 = s2;
	if (!n)
		return (0);
	while (tmp_s1[i] == tmp_s2[i] && i < n - 1)
		i++;
	return (tmp_s1[i] - tmp_s2[i]);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = b;
	while (i < len)
		tmp[i++] = c;
	return (tmp);
}
