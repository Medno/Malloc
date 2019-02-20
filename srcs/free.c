#include "lib_alloc.h"

void	free_n(void *ptr)
{
	t_block	*found;
	t_alloc	type;

	type = TINY_TYPE;
	if (!ptr)
		return ;
	found = find_block_of_ptr(ptr, &type);
	if (!found)
		return ;
	found->free = 1;
	if (type == LARGE_TYPE)
	{
		found->next = NULL;
		found->prev = NULL;
		munmap(found, found->size + sizeof(t_block));
		return ;
	}
	defragment_around(found);
	return ;
}

void	free(void *ptr)
{
	free_n(ptr);
}
