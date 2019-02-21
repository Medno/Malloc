#include "lib_alloc.h"

void	free_n(void *ptr)
{
	t_block	*found;
	t_alloc	type;

	type = TINY_TYPE;
	found = find_block_of_ptr(ptr, &type);
	if (!found)
		return ;
	found->free = 1;
	if (type == LARGE_TYPE)
	{
		if (found->next)
			found->next->prev = found->prev;
		if (!found->prev)
			g_pool[type] = (found->next) ? found->next : NULL;
		else
			found->prev->next = found->next;
		found->next = NULL;
		found->prev = NULL;

		if ((munmap(found, align_size(found->size + sizeof(t_block), 4))) == -1)
			ft_putendl_fd("Error unmapping memory", 2);
		return ;
	}
	defragment_around(found);
	return ;
}

void	free(void *ptr)
{
	free_n(ptr);
}
