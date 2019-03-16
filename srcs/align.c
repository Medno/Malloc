/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 10:28:10 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/08 14:30:12 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

size_t	align_size(size_t size, int round)
{
	if (!size)
		return (round);
	return ((((size - 1) / round) * round) + round);
}
