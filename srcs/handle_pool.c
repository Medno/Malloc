#include "lib_alloc.h"

size_t	compute_size_to_allocate(size_t size, t_alloc type)
{
	if (type == TINY_TYPE)
		return ((TINY + sizeof(t_block)) * NB_ALLOCATION);
	else if (type == SMALL_TYPE)
		return ((SMALL + sizeof(t_block)) * NB_ALLOCATION);
	return (size + sizeof(t_block));
}

t_block	*create_free_block(t_block *new, size_t total_size, t_block *last)
{
	t_block	*freed;

	freed = (t_block *)((char *)new + new->size + sizeof(t_block));
	freed->next = last ? last->next : NULL;
	freed->prev = new;
	freed->size = total_size - new->size - sizeof(t_block);
	freed->free = 1;
	return (freed);
}

void	*extend_heap(size_t size, t_alloc type, t_block *last)
{
	t_block	*new_block;
	size_t	aligned_pages;
	size_t	size_to_allocate;
	
	size_to_allocate = compute_size_to_allocate(size, type);
//ft_putnbr(size_to_allocate);
//ft_putendl(" <-- size_to_alloc");
	aligned_pages = align_size(size_to_allocate, getpagesize());
//ft_putnbr(aligned_pages);
//ft_putendl(" <-- size_alloc");
//ft_putnbr(size);
//ft_putendl(" <-- size");
	new_block = (t_block *)alloc_mem(last, aligned_pages);
	if (!new_block)
		return (NULL);
	new_block->size = size;
	new_block->prev = last;
	new_block->next = (type == LARGE_TYPE) ? NULL :
		create_free_block(new_block, aligned_pages, last);
	if (last)
		(last)->next = new_block;
	else
		g_pool[type] = new_block;
//handle_addr((size_t)g_pool[type], 16);
//ft_putendl(" <-- pool");
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

void	*handle_pool(size_t size, t_alloc type)
{
	t_block	*block;
	t_block	*last;

	last = g_pool[type];
	block = find_available_chunk(size, type, last);
	if (block)
	{
		if (block->size - size >= sizeof(t_block) + 4)
			split_block(size, block);
		block->free = 0;
	}
	else
		block = extend_heap(size, type, last);
//print_all_pools();
	return (block);
}
