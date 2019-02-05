/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:06:22 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 14:24:44 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nb_words(char const *s, char c)
{
	size_t	res;
	int		i;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			res++;
			while (s[i + 1] && s[i] != c)
				i++;
		}
		i++;
	}
	return (res);
}

static void		tmp(char **tab, char const *s, char c, size_t *i_tab)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = 0;
			while (s[i + len] != c && s[i + len])
				len++;
			tab[*i_tab] = ft_strsub(s, i, len);
			(*i_tab)++;
			i += len;
		}
		i = (s[i]) ? i + 1 : i;
	}
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	j;

	j = 0;
	if (s && c)
	{
		if (!(tab = (char **)malloc(sizeof(char *) * nb_words(s, c) + 1)))
			return (NULL);
		tmp(tab, s, c, &j);
		tab[j] = 0;
		return (tab);
	}
	return (NULL);
}
