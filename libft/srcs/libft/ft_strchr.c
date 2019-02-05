/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:03:54 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/26 11:16:41 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;

	tmp = (char *)s;
	while (*tmp)
	{
		if (*tmp == c)
			return (tmp);
		tmp++;
	}
	if (*tmp == '\0' && c == '\0')
		return (tmp);
	return (NULL);
}

char	*ft_strfchr(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && str[i - 1])
			return (ft_strsub(str, 0, i));
		i++;
	}
	return (NULL);
}

char	*ft_strlchr(const char *s, int c)
{
	char	*tmp;
	char	*res;
	int		i;
	int		max;

	i = 0;
	max = -1;
	tmp = ft_strdup(s);
	while (tmp[i])
	{
		if (tmp[i] == c)
			max = i;
		i++;
	}
	if (tmp[i] == '\0' && c == '\0')
		max = i;
	if (max == -1)
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	tmp[max + 1] = '\0';
	res = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (res);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		i;
	int		max;

	i = 0;
	max = -1;
	tmp = (char *)s;
	while (tmp[i])
	{
		if (tmp[i] == c)
			max = i;
		i++;
	}
	if (tmp[i] == '\0' && c == '\0')
		max = i;
	if (max == -1)
		return (NULL);
	return (tmp + max);
}
