/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:06:16 by pchadeni          #+#    #+#             */
/*   Updated: 2017/11/09 16:25:29 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*tmp;

	if (s)
	{
		if ((tmp = ft_strnew(len)))
		{
			if (start + len <= ft_strlen(s))
			{
				tmp = ft_strncpy(tmp, s + start, len);
				tmp[len] = '\0';
			}
			return (tmp);
		}
	}
	return (NULL);
}
