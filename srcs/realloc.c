#include "lib_alloc.h"

void	reduce_size_of_current_block(size_t size, t_alloc type, t_block *block)
{
	t_block	*new;
	t_block	*last;

	new = split_block(size, block);
	last = find_last_block(g_pool[type].freed, new);
	if (last)
	{
		if (last->prev)
			last->new->prev = new;
		new->next = last->next;
		new->prev = last;
		last->next = new;
	}
	else
	{
		last = new;
		new->next = NULL;
		new->prev = NULL;
	}
}

void	*realloc(void *ptr, size_t size)
{
	size_t	aligned_size;
	t_block	*block;
	t_alloc	type;

	if (!ptr)
		return (malloc(size));
	type = TINY_TYPE;
	block = find_block_of_ptr(ptr, &type);
	if (block)
	{
		aligned_size = align_size(size, 4)
			if (block->size >= aligned_size)
			{
				if (block->size - aligned_size >= sizeof(t_block))
					reduce_size_of_current_block(aligned_size, type, block);
			}

	}
	return (NULL);
}
