/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:37:59 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/16 16:12:00 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

static void	*new_malloc(size_t size, void *ptr, t_block *block)
{
	void	*new_ptr;
	size_t	min_size;

	new_ptr = malloc_n(size);
	if (!new_ptr)
		return (NULL);
	min_size = block->size < size ? block->size : size;
	new_ptr = ft_memcpy(new_ptr, ptr, min_size);
	free_n(ptr);
	return (new_ptr);
}

static void	*handle_realloc_block(void *p, size_t size, t_block *block)
{
	if (block->size >= size)
	{
		if (block->size - size >= sizeof(t_block))
			block->next = split_block(size, block);
	}
	else
	{
		if (block->next && block->next->free &&
				block->size + sizeof(t_block) + block->next->size >= size)
		{
			defragment_around(block);
			if (block->size - size >= sizeof(t_block))
				block->next = split_block(size, block);
		}
		else
			return (new_malloc(size, p, block));
	}
	defragment_around(block->next);
	return ((void *)((char *)block + sizeof(t_block)));
}

static void	*handle_realloc(void *ptr, size_t size, t_block *bl, t_alloc type)
{
	t_alloc	new_type;

	if (size == bl->size)
		return (ptr);
	new_type = find_type_pool(size);
	if (new_type == type && type != LARGE_TYPE)
		return (handle_realloc_block(ptr, size, bl));
	return (new_malloc(size, ptr, bl));
}

void		*realloc_n(void *ptr, size_t size)
{
	t_bucket	*nul;
	t_block		*block;
	t_alloc		type;
	size_t		aligned_size;

	if (!ptr)
		return (malloc_n(size));
	if (ptr && !size)
	{
		free_n(ptr);
		return (malloc_n(0));
	}
	type = TINY_TYPE;
	block = find_block_of_ptr(ptr, &type, &nul);
	aligned_size = align_size(size, ALIGN);
	if (!aligned_size)
		return (NULL);
	return (block ? handle_realloc(ptr, aligned_size, block, type) : NULL);
}

void		*realloc(void *ptr, size_t size)
{
	void	*res;

	pthread_mutex_lock(&g_mutex);
	res = realloc_n(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (res);
}
