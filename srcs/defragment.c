#include "lib_alloc.h"

void	defragment_chunk(t_block *old, t_block *new)
{
	if (old && (size_t)old + old->size + sizeof(t_block) == (size_t)new)
	{
		old->size += new->size + sizeof(t_block);
		old->next = new->next;
		if (new->next)
			new->next->prev = old;
		new->size = 0;
		new->prev = NULL;
		new->next = NULL;
	}
}

void	defragment_around(t_block *new_freed)
{
	t_block	*tmp;

	tmp = new_freed->prev;
	if (tmp)
		defragment_chunk(tmp, new_freed);
	else
		tmp = new_freed;
	if (tmp && tmp->next)
	{
		new_freed = tmp->next;
		defragment_chunk(tmp, new_freed);
	}
}
