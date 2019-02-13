#include "lib_alloc.h"

t_block	*search_available_chunk(size_t size, t_alloc type)
{
	t_block	*tmp;

	tmp = g_pool[type].freed;
	while (tmp && tmp->size >= size)
		tmp = tmp->next;
	return (tmp);
}

t_block	*find_last_block(t_block *pool)
{
	t_block	*tmp;

	tmp = pool;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}
