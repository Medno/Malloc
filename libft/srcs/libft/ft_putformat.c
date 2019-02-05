/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 10:58:47 by pchadeni          #+#    #+#             */
/*   Updated: 2017/12/18 14:23:18 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putformat(char *str, char *color, char *background)
{
	if (color != NULL)
		ft_putstr(color);
	if (background != NULL)
		ft_putstr(background);
	ft_putstr(str);
	ft_putstr("\033[0m");
}
