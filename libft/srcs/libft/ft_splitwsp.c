/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwsp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:37:07 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/23 18:05:43 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len_wsp(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_iswsp(str[i]))
		i++;
	return (i);
}

char			**ft_splitwsp(char *str)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * ft_nbwords(str) + 1)) ||
			!len_wsp(str))
		return (NULL);
	while (str[i])
	{
		if (ft_iswsp(str[i]))
			i++;
		else
		{
			tab[j] = ft_strsub(str, i, len_wsp(str + i));
			i += ft_strlen(tab[j]);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
