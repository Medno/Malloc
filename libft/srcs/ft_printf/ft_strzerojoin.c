/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strzerojoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 08:56:28 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/26 10:46:33 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strzerocat(char *s1, char *s2, int len1, int len2)
{
	int	j;

	j = 0;
	while (j < len2)
	{
		s1[len1] = s2[j];
		len1++;
		j++;
	}
	s1[len1] = '\0';
	return (s1);
}

char	*ft_strjoinzero(char *s1, char *s2, int len1, int len2)
{
	char	*tmp;

	if (s1 && s2)
	{
		if ((tmp = ft_strnew(len1 + len2)))
		{
			tmp = ft_strzerocat(tmp, s1, 0, len1);
			tmp = ft_strzerocat(tmp, s2, len1, len2);
			ft_strdel(&s1);
			return (tmp);
		}
	}
	else if (s1)
		return (s1);
	return (NULL);
}
