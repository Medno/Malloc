#include "lib_alloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

t_block	*alloc_mem(void *start_addr, size_t size)
{
	t_block	*tmp;

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

t_alloc	find_type_pool(size_t size)
{
	if (size <= TINY)
		return (TINY_TYPE);
	else if (size <= SMALL)
		return (SMALL_TYPE);
	return (LARGE_TYPE);
}

void	*calloc(size_t count, size_t size)
{
	void	*result;

//ft_putendl("Start of calloc");
	pthread_mutex_lock(&g_mutex);
	result = malloc_n(count * size);
	if (result)
		ft_bzero(result, count * size);
	pthread_mutex_unlock(&g_mutex);
//ft_putendl("End of calloc");
	return (result);
}

void	*malloc_n(size_t size)
{
	size_t	aligned_size;
	void	*result;
	t_alloc	type;

	aligned_size = align_size(size, 16);
	type = find_type_pool(aligned_size);
	result = handle_pool(aligned_size, type);
	return ((void *)result + sizeof(t_block));
}

void	*malloc(size_t size)
{
	void	*res;

ft_putendl("Before Malloc");
	pthread_mutex_lock(&g_mutex);
	res = malloc_n(size); 
	pthread_mutex_unlock(&g_mutex);
//handle_addr((size_t)res, 10);
//ft_putendl(" <-- Result");
print_all_pools();
handle_addr(getpagesize(), 10);
ft_putendl(" <-- Pagesize");
//ft_putendl("After Malloc");
	return (res);
}
