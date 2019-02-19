#include "lib_alloc.h"

t_block	*find_block_of_ptr(void *ptr, t_alloc *type)
{
	t_block	*result;

	result = NULL;
	while (*type <= LARGE_TYPE && !result)
	{
		result = find_last_block(g_pool[*type].alloc,
				(t_block *)(ptr - sizeof(t_block)));
		if (!result)
			(*type)++;
	}
	if (result && !result->next &&
			(t_block *)(ptr - sizeof(t_block)) != result)
		return (NULL);
	return (result);
}

void	insert_in_free_list(t_block *to_insert, t_block *last, t_alloc type)
{
	if (last > to_insert)
	{
		if (last->prev)
			last->prev->next = to_insert;
		else
			g_pool[type].freed = to_insert;
		to_insert->next = last;
		to_insert->prev = last->prev;
		last->prev = to_insert;
	}
	else
	{
		to_insert->next = last->next;
		to_insert->prev = last;
		last->next = to_insert;
	}
}

void	move_found_to_free(t_block *alloc_to_freed, t_alloc type)
{
	t_block	*freed;

	freed = find_last_block(g_pool[type].freed, alloc_to_freed);
	if (alloc_to_freed->prev)
		alloc_to_freed->prev->next = alloc_to_freed->next;
	else
		g_pool[type].alloc = alloc_to_freed->next;
	if (alloc_to_freed->next)
		alloc_to_freed->next->prev = alloc_to_freed->prev;
	if (freed)
		insert_in_free_list(alloc_to_freed, freed, type);
	else
		freed = alloc_to_freed;
}

void	free(void *ptr)
{
	t_block	*found;
	t_alloc	type;

	type = TINY_TYPE;
	if (!ptr)
		return ;
	found = find_block_of_ptr(ptr, &type);
	if (!found)
		return ;
	move_found_to_free(found, type);
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
