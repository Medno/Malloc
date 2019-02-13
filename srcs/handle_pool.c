#include "lib_alloc.h"

size_t	compute_size_to_allocate(size_t size, t_alloc type)
{
	if (type == TINY_TYPE)
		return (TINY + sizeof(t_block) * NB_ALLOCATION);
	else if (type == SMALL_TYPE)
		return (SMALL + sizeof(t_block) * NB_ALLOCATION);
	return (size + sizeof(t_block));
}

void	*extend_heap(size_t size, t_alloc type)
{
	t_block	*new_block;
	t_block	*last;
	size_t	aligned_pages;
	size_t	size_to_allocate;
	
	new_block = NULL;
	size_to_allocate = compute_size_to_allocate(size, type);
	last = find_last_block(g_pool[type].freed);
	//last ou last + size etc. ?
	aligned_pages = align_size(size_to_allocate, getpagesize());
	new_block = (t_block *)alloc_mem(last, aligned_pages);

	if (!new_block)
		return (NULL);
	new_block->size = size_to_allocate - sizeof(t_block);
	new_block->next = NULL;
	new_block->prev = last;
	if (last)
		last->next = new_block;
ft_printf("Type:			%d\n", type);
ft_printf("Last:			%p\nNew:			%p\n", last, new_block);
ft_printf("Size to allocate:	|%zu|\n", size_to_allocate);
ft_printf("Pages to allocate:	|%zu|\n", aligned_pages);
ft_printf("Size of block:		|%zu|\n", sizeof(t_block));
ft_printf("Size of block & siz:	|%zu|\n", sizeof(t_block) + size);

	return (new_block);
}

t_block	*split_block(size_t size, t_block *to_split, t_block *last_allocated)
{
	t_block	*new;

	new = NULL;
	new->size = size;
	new->next = NULL;
	new->prev = last_allocated;
	last_allocated->next = new;
	if (!(to_split->size - size))
	{
		to_split->prev->next = to_split->next;
		to_split->next = NULL;
	}
	to_split->size -= size;
	return (new);
}

void	*handle_available_block(size_t size, t_alloc type, t_block *block)
{
	t_block	*new;

	new = find_last_block(g_pool[type].alloc);
	new->next = split_block(size, block, new);
	return (new->next + sizeof(t_block));
}

void	*handle_pool(size_t size, t_alloc type)
{
	t_block	*block;

	block = NULL;
	block = search_available_chunk(size, type);
	if (block)
		return (handle_available_block(size, type, block));
	else
		return (extend_heap(size, type));
}
