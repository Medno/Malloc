/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:34:17 by pchadeni          #+#    #+#             */
/*   Updated: 2019/02/25 16:34:22 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

void	defragment_chunk(t_block *old, t_block *new)
{
	if (old && (size_t)old + old->size + sizeof(t_block) == (size_t)new)
	{
		old->size += new->size + sizeof(t_block);
		old->next = new->next;
		if (new->next)
			new->next->prev = old;
	}
}

void	defragment_around(t_block *new_freed)
{
	t_block	*tmp;

	tmp = new_freed->prev;
	if (tmp && tmp->free)
		defragment_chunk(tmp, new_freed);
	else
		tmp = new_freed;
	if (tmp && tmp->next && tmp->next->free)
	{
		new_freed = tmp->next;
		defragment_chunk(tmp, new_freed);
	}
}
