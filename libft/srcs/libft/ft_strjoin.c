/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 08:56:28 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 11:49:14 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;

	if (s1 && s2)
	{
		if ((tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		{
			tmp = ft_strcat(tmp, s1);
			tmp = ft_strcat(tmp, s2);
			return (tmp);
		}
	}
	return (NULL);
}

char	*ft_strjoindel(char *s1, char *s2)
{
	char	*tmp;

	if (s1 && s2)
	{
		if ((tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		{
			tmp = ft_strcat(tmp, s1);
			tmp = ft_strcat(tmp, s2);
			ft_strdel(&s1);
			return (tmp);
		}
	}
	else if (s1)
		return (s1);
	return (NULL);
}

char	*ft_onejoinf(char *news, char *old)
{
	char	*tmp;
	int		i;
	int		j;

	if (news && old && (tmp = ft_strnew(ft_strlen(news) + ft_strlen(old))))
	{
		i = 0;
		j = ft_strlen(news);
		tmp = ft_strcat(tmp, news);
		while (old[i])
		{
			if (!ft_strchr(tmp, old[i]))
			{
				tmp[j] = old[i];
				j++;
			}
			i++;
		}
		tmp[j] = '\0';
		ft_strdel(&news);
		news = ft_strdup(tmp);
		ft_strdel(&tmp);
		return (news);
	}
	return (NULL);
}

char	*ft_put_in_str(char *str, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	if (!str)
	{
		str = ft_strnew(1);
		str[0] = c;
	}
	else
		str = ft_strjoindel(str, tmp);
	return (str);
}
