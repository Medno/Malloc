/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkopt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 17:26:40 by pchadeni          #+#    #+#             */
/*   Updated: 2018/01/16 18:03:15 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_checkopt(char *p, char *str, int nb_opt)
{
	char	valid[nb_opt];
	int		i;

	i = 0;
	if (p)
	{
		ft_strcpy(valid, str);
		while (p[i])
		{
			if (!ft_strchr(valid, p[i]))
				return (p[i]);
			i++;
		}
		return (0);
	}
	return (0);
}
