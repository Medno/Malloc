/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:34:17 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/06 11:34:14 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

t_block	*defragment_around(t_block *new_freed)
{
	if (new_freed && new_freed->next && new_freed->next->free)
	{
		new_freed->size += new_freed->next->size + sizeof(t_block);
		new_freed->next = new_freed->next->next;
		if (new_freed->next)
			new_freed->next->prev = new_freed;
	}
	return (new_freed);
}
