/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putform.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:09:04 by pchadeni          #+#    #+#             */
/*   Updated: 2017/12/18 14:23:43 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcolor(char *str, char *color)
{
	if (color != NULL)
		ft_putstr(color);
	ft_putstr(str);
	ft_putstr("\033[0m");
}
