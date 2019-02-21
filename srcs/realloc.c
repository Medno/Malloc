#include "lib_alloc.h"

void	*new_malloc(size_t size, void *ptr, t_alloc type, t_block *block)
{
	void	*new_ptr;
	t_block	*new_block;
	size_t	min_size;

	new_ptr = malloc_n(size);
	if (!new_ptr)
		return (NULL);
	new_block = find_block_of_ptr(new_ptr, &type);
	min_size = block->size < size ? block->size : size;
	new_ptr = ft_memcpy(new_ptr, ptr, min_size);
	free_n(ptr);
//print_all_pools();
//ft_putendl("Test");
	return (new_ptr);
}

void	*handle_realloc_block(void *p, size_t size, t_block *block, t_alloc t)
{
	if (block->size >= size)
	{
		if (block->size - size >= sizeof(t_block) + 4)
			split_block(size, block);
	}
	else
	{
		if (block->next && block->next->free &&
			block->size + sizeof(t_block) + block->next->size >= size)
		{
			defragment_around(block);
			if (block->size - size >= sizeof(t_block))
				split_block(size, block);
		}
		else
			return (new_malloc(size, p, t, block));
	}
	return ((void *)((char *)block + sizeof(t_block)));
}

void	*realloc_n(void *ptr, size_t size)
{
	t_block	*block;
	t_alloc	type;
	t_alloc	new_type;
	size_t	aligned_size;

	if (!ptr)
		return (malloc_n(size));
	if (ptr && !size)
	{
		free_n(ptr);
		return (malloc_n(TINY));
	}
	type = TINY_TYPE;
	block = find_block_of_ptr(ptr, &type);
	aligned_size = align_size(size, 4);
	new_type = find_type_pool(aligned_size);
	if (block && new_type == type)
		return (handle_realloc_block(ptr, aligned_size, block, type));
	else if (block)
		return (new_malloc(size, ptr, new_type, block));
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	void	*res;

	res = realloc_n(ptr, size);
	return (res);
}
