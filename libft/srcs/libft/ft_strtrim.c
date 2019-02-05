/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 09:14:14 by pchadeni          #+#    #+#             */
/*   Updated: 2017/11/09 10:04:38 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*tmp;
	size_t	start;
	size_t	len;
	size_t	i;

	start = 0;
	len = 0;
	i = 0;
	if (s)
	{
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
			i++;
		start = i;
		while (s[i])
		{
			if (s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
				len = i - start;
			i++;
		}
		if ((tmp = ft_strnew(len)))
			return ((tmp = ft_strsub(s, start, len + 1)));
	}
	return (NULL);
}
