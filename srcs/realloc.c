/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:37:59 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/08 14:19:37 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

void	*new_malloc(size_t size, void *ptr, t_block *block)
{
	void	*new_ptr;
	size_t	min_size;

	new_ptr = malloc_n(size);
	handle_addr((uintptr_t)new_ptr, 16);
	ft_putendl(" <-- New pointer");

	if (!new_ptr)
		return (NULL);
	min_size = block->size < size ? block->size : size;
	handle_addr(size, 10);
	ft_putendl(" <-- to size");
	handle_addr(block->size, 10);
	ft_putendl(" <-- to block size");

	new_ptr = ft_memcpy(new_ptr, ptr, min_size);
	free_n(ptr);
	return (new_ptr);
}

void	*handle_realloc_block(void *p, size_t size, t_block *block)
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
	return ((void *)block + sizeof(t_block));
}

void	*realloc_n(void *ptr, size_t size)
{
	t_block	*block;
	t_alloc	type;
	t_alloc	new_type;
	size_t	aligned_size;
	t_bucket	*nul;

	if (!ptr)
		return (malloc_n(size));
	if (ptr && !size)
	{
		free_n(ptr);
		return (malloc_n(0));
	}
	type = TINY_TYPE;

	block = find_block_of_ptr(ptr, &type, &nul);
	if (block)
	{
		handle_addr((size_t)block, 16);
		ft_putendl(" <-- to allocate");
		handle_addr(block->size, 10);
		ft_putendl(" <-- to allocate");

	}
	aligned_size = align_size(size, 32);
	if (!aligned_size)
		return (NULL);
	new_type = find_type_pool(aligned_size);
handle_addr(size, 10);
ft_putendl(" <-- size before reallocing to allocate");
handle_addr(new_type, 10);
ft_putendl(" <-- type before reallocing to allocate");
	if (block && new_type == type && type != LARGE_TYPE)
		return (handle_realloc_block(ptr, aligned_size, block));
	else if (block)
		return (new_malloc(size, ptr, block));
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	void	*res;

	pthread_mutex_lock(&g_mutex);
handle_addr((size_t)ptr, 16);
ft_putendl(" <-- Before realloc");
handle_addr(size, 10);
ft_putendl(" <-- to allocate");

print_all_pools();
	res = realloc_n(ptr, size);
print_all_pools();
handle_addr((size_t)res, 16);
ft_putendl(" <-- after realloc");
	pthread_mutex_unlock(&g_mutex);
	return (res);
}
