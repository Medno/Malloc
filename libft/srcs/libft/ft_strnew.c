/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:32:38 by pchadeni          #+#    #+#             */
/*   Updated: 2017/11/25 11:45:20 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (size > i)
	{
		tmp[i] = '\0';
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
