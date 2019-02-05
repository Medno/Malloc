/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:21:25 by pchadeni          #+#    #+#             */
/*   Updated: 2019/01/17 18:19:54 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	char	**tmp;
	int		size;

	if (!tab)
		return (NULL);
	size = 0;
	while (tab[size])
		size++;
	if (!(tmp = (char **)malloc(sizeof(char *) * size + 1)))
		return (NULL);
	tmp[size] = NULL;
	size--;
	while (size >= 0)
	{
		tmp[size] = ft_strdup(tab[size]);
		size--;
	}
	return (tmp);
}

void	ft_tabdel(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			ft_strdel(&(tab[i]));
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	ft_del_array(void **array)
{
	int i;

	i = -1;
	if (array)
	{
		while (array[++i])
		{
			free(array[i]);
			array[i] = NULL;
		}
		free(array);
		array = NULL;
	}
}

void	ft_puttab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
}
