/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:50:08 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/16 16:11:00 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

size_t	compute_size_to_allocate(size_t size, t_alloc type)
{
	size_t	bucket_size;

	bucket_size = align_size(sizeof(t_bucket), ALIGN);
	if (type == TINY_TYPE)
		return (bucket_size + ((TINY + sizeof(t_block)) * NB_ALLOCATION));
	else if (type == SMALL_TYPE)
		return (bucket_size + ((SMALL + sizeof(t_block)) * NB_ALLOCATION));
	return (bucket_size + size + sizeof(t_block));
}

void	*extend_heap(size_t size, t_alloc type, t_bucket *last)
{
	size_t		buck_size;
	size_t		aligned_pages;
	size_t		size_to_allocate;
	t_bucket	*new_bucket;

	size_to_allocate = compute_size_to_allocate(size, type);
	aligned_pages = align_size(size_to_allocate, getpagesize());
	new_bucket = alloc_mem(last, aligned_pages);
	if (!new_bucket)
		return (NULL);
	buck_size = align_size(sizeof(t_bucket), ALIGN);
	new_bucket->prev = last;
	new_bucket->next = NULL;
	new_bucket->end = (char *)new_bucket + aligned_pages;
	new_bucket->block = (t_block *)((char *)new_bucket + buck_size);
	new_bucket->block->size = aligned_pages - sizeof(t_block) - buck_size;
	new_bucket->block->prev = NULL;
	new_bucket->block->next = NULL;
	new_bucket->block->free = 0;
	if (last)
		last->next = new_bucket;
	else
		g_pool[type] = new_bucket;
	return (new_bucket->block);
}

t_block	*split_block(size_t size, t_block *to_split)
{
	t_block	*new;

	new = (t_block *)((char *)to_split + sizeof(t_block) + size);
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
