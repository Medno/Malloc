#include "lib_alloc.h"

void	*alloc_mem(void *start_addr, size_t size)
{
	void	*tmp;

	if ((tmp = mmap(start_addr, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (tmp);
}

size_t	align_size(size_t size, int round)
{
	if (!size)
		return (round);
	return ((((size - 1) / round) * round) + round);
}

//EDIT: Name of function
t_alloc	find_type_pool(size_t size)
{
	if (size <= TINY)
		return (TINY_TYPE);
	else if (size <= SMALL)
		return (SMALL_TYPE);
	return (LARGE_TYPE);
}

void	*malloc(size_t size)
{
	size_t	aligned_size;
	void	*result;
	t_alloc	type;

	aligned_size = align_size(size, 4);
ft_printf("Initial size:		|%zu|\nAligned size:		|%zu|\n", size, aligned_size);
	type = find_type_pool(aligned_size);
	if (type == LARGE_TYPE)
		result = extend_heap(aligned_size, type);
	else
		result = handle_pool(aligned_size, type);
	return (result);
}
