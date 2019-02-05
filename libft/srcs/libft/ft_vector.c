/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 10:59:23 by pchadeni          #+#    #+#             */
/*   Updated: 2019/01/17 18:19:38 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_squared_vector_distance(t_point a, t_point b)
{
	return ((unsigned int)ft_pow(b.x - a.x, 2) + ft_pow(b.y - a.y, 2));
}
