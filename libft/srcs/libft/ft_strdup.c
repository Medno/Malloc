/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:25:14 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/20 10:39:37 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen((char *)s1) + 1)))
		return (NULL);
	while (i < ft_strlen((char *)s1))
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strndup(const char *s1, size_t len)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strdup_count(const char *s1, const char searched, int *count)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * ft_strlen((char *)s1) + 1)))
		return (NULL);
	while (i < ft_strlen((char *)s1))
	{
    if (s1[i] == searched)
      *count = *count + 1;
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
