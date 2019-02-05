/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strgap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 10:18:08 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 13:09:47 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strgap(char *str, char delim, int pos)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = str;
	while (s[i] && j < pos)
	{
		if (s[i] == delim)
		{
			j++;
			if (j == pos)
				return (ft_strsub(s, 0, i));
			else
			{
				s += i + 1;
				i = -1;
			}
		}
		i++;
	}
	return ((pos - 1 == ft_nbchar(str, ':')) ? ft_strsub(s, 0, i) : NULL);
}

char	*ft_strlgap(char *str, char delim, int pos)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = str;
	while (s[i] && j <= pos)
	{
		if (s[i] == delim && i != 0)
		{
			j++;
			if (j == pos)
				return (ft_strsub(s, 0, i));
		}
		i++;
	}
	return ((pos - 1 <= ft_nbchar(str, delim)) ? ft_strsub(s, 0, i) : NULL);
}
