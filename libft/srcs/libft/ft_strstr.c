/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:44:05 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 13:06:36 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*tmp_hay;
	char	*tmp_needle;

	i = 0;
	j = 0;
	tmp_hay = (char *)haystack;
	tmp_needle = (char *)needle;
	if (*tmp_needle == '\0')
		return (tmp_hay);
	while (tmp_hay[i])
	{
		j = 0;
		if (tmp_hay[i] == tmp_needle[j])
			while (tmp_hay[i + j] == tmp_needle[j] || tmp_needle[j] == '\0')
			{
				if (tmp_needle[j] == '\0')
					return (&tmp_hay[i]);
				j++;
			}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	n++;
	while (haystack[i] && n)
	{
		j = 0;
		if (haystack[i] == needle[j])
			while ((haystack[i + j] == needle[j] || needle[j] == '\0') && n)
			{
				if (needle[j] == '\0')
					return ((char *)&haystack[i]);
				j++;
				n--;
			}
		n = n + j - 1;
		i++;
	}
	return (NULL);
}
