/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:50:08 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/06 17:08:28 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

size_t	align_size(size_t size, int round)
{
	if (!size)
		return (round);
	return ((((size - 1) / round) * round) + round);
}

size_t	compute_size_to_allocate(size_t size, t_alloc type)
{
	if (type == TINY_TYPE)
		return (sizeof(t_bucket) + (TINY + sizeof(t_block)) * NB_ALLOCATION);
	else if (type == SMALL_TYPE)
		return (sizeof(t_bucket) + (SMALL + sizeof(t_block)) * NB_ALLOCATION);
	return (size + sizeof(t_block));
}

void	*extend_heap(size_t size, t_alloc type, t_bucket *last)
{
	// t_block		*new_block;
	size_t		aligned_pages;
	size_t		size_to_allocate;
	t_bucket	*new_bucket;

	size_to_allocate = compute_size_to_allocate(size, type);
	aligned_pages = align_size(size_to_allocate, getpagesize());
	new_bucket = alloc_mem(last, aligned_pages);
	if (!new_bucket)
		return (NULL);
	new_bucket->next = NULL;
	new_bucket->block = (t_block *)((uintptr_t)new_bucket + sizeof(t_bucket));
	new_bucket->block->size = aligned_pages - sizeof(t_block);
	new_bucket->block->prev = NULL;
	new_bucket->block->next = NULL;
	if (last)
		last->next = new_bucket;
	else
		g_pool[type] = new_bucket;
	new_bucket->block->free = 0;
	return (new_bucket->block);
}

t_block	*split_block(size_t size, t_block *to_split)
{
	t_block	*new;

	new = (t_block *)((uintptr_t)to_split + sizeof(t_block) + size);
	new->size = to_split->size - size - sizeof(t_block);
	new->next = to_split->next;
	new->prev = to_split;
	new->free = 1;
	if (to_split->next)
		to_split->next->prev = new;
	to_split->size = size;
	to_split->next = new;
	return (new);
}

t_block	*handle_pool(size_t size, t_alloc type)
{
	t_block		*block;
	t_bucket	*last;

	last = g_pool[type];
	block = find_available_chunk(size, type, &last);
	if (type == LARGE_TYPE)
		return (extend_heap(size, type, last));
	if (block)
		block->free = 0;
	else
		block = extend_heap(size, type, last);
	if (block->size - size >= sizeof(t_block))
		block->next = split_block(size, block);
	return (block);
}
