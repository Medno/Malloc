/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:10:18 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 11:43:48 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char		*tmp;
	const char	*tmp_s;
	size_t		i;

	i = 0;
	tmp = NULL;
	if (s)
	{
		tmp_s = s;
		if ((tmp = ft_strnew(ft_strlen(tmp_s))))
		{
			while (tmp_s[i])
			{
				tmp[i] = (*f)(tmp_s[i]);
				i++;
			}
			tmp[i] = '\0';
		}
	}
	return (tmp);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	const char	*tmp_s;
	char		*tmp;
	size_t		i;

	i = 0;
	tmp = NULL;
	if (s)
	{
		tmp_s = s;
		if ((tmp = ft_strnew(ft_strlen(tmp_s))))
		{
			while (tmp_s[i])
			{
				tmp[i] = (*f)(i, tmp_s[i]);
				i++;
			}
			tmp[i] = '\0';
		}
	}
	return (tmp);
}
