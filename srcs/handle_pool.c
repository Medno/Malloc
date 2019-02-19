#include "lib_alloc.h"

size_t	compute_size_to_allocate(size_t size, t_alloc type)
{
	if (type == TINY_TYPE)
		return ((TINY + sizeof(t_block)) * NB_ALLOCATION);
	else if (type == SMALL_TYPE)
		return ((SMALL + sizeof(t_block)) * NB_ALLOCATION);
	return (size + sizeof(t_block));
}

void	create_new_pool(t_alloc type, t_block *new, size_t total_size)
{
	t_pool	*pool;
	t_block	*freed;

	pool = &g_pool[type];
	pool->alloc = new;
	freed = (t_block *)((char *)new + new->size + sizeof(t_block));
	freed->next = NULL;
	freed->prev = NULL;
	freed->size = total_size - new->size - sizeof(t_block);
	pool->freed = freed;

}

void	*extend_heap(size_t size, t_alloc type, t_block *last)
{
	t_block	*new_block;
	t_block	*last;
	size_t	aligned_pages;
	size_t	size_to_allocate;
	
	size_to_allocate = compute_size_to_allocate(size, type);
	aligned_pages = align_size(size_to_allocate, getpagesize());
	new_block = (t_block *)alloc_mem(last, aligned_pages);
	if (!new_block)
		return (NULL);
	new_block->size = size;
	new_block->next = NULL;
	new_block->prev = last;
	if (last)
		last->next = new_block;
	else
		last = new_block;
	new_block->free = 0;
	return (new_block);
}

t_block	*split_block(size_t size, t_block *to_split)
{
	t_block	*new;

	new = (t_block *)((char *)to_split + sizeof(t_block) + size);
	new->size = to_split->size - size - sizeof(t_block);
	new->next = to_split->next;
	new->prev = to_split;
	new->free = 1;
	to_split->size = size;
	to_split->next = new;
	return (new);
}

void	*handle_available_block(size_t size, t_alloc type, t_block *freed)
{
	t_block	*last_alloc;
	t_block	*new_freed;

	last_alloc = find_last_block(g_pool[type].alloc, freed);
	new_freed = split_block(size, freed);
	new_freed->prev = freed->prev ? freed->prev : NULL;
	new_freed->next = freed->next ? freed->next : NULL;
	if (freed->prev)
		freed->prev->next = new_freed;
	else
		g_pool[type].freed = new_freed;
	if (last_alloc)
	{
		freed->next = last_alloc->next;
		last_alloc->next = freed;
		freed->prev = last_alloc;
	}
	else
	{
		freed->prev = NULL;
		freed->next = NULL;
		g_pool[type].alloc = freed;
	}
	return (last_alloc->next);
}

void	*handle_pool(size_t size, t_alloc type)
{
	t_block	*block;
	t_block	*last;

	block = search_available_chunk(size, type, last);
	if (block)
		return (handle_available_block(size, type, block));
	return (extend_heap(size, type, last));
}
