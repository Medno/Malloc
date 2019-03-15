/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:36:30 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/08 14:15:08 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

t_bucket	*alloc_mem(void *start_addr, size_t size)
{
	t_bucket	*tmp;

handle_addr(size, 10);
ft_putendl(" <-- Alloc_mem -> size");

handle_addr((size_t)start_addr, 16);
ft_putendl(" <-- Alloc_mem -> start_addr");

	if ((tmp = mmap(start_addr, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (tmp);
}

t_alloc	find_type_pool(size_t size)
{
	if (size <= TINY)
		return (TINY_TYPE);
	else if (size <= SMALL)
		return (SMALL_TYPE);
	return (LARGE_TYPE);
}

uint8_t	above_limit(size_t size)
{
	struct rlimit	limit;

	if (getrlimit(RLIMIT_DATA, &limit))
		return (1);
	handle_addr(limit.rlim_cur, 10);
	ft_putendl(" <-- current limit");
	handle_addr(size, 10);
	ft_putendl(" <-- mysize");
	if (size > limit.rlim_cur || size == 0)
		return (1);
	return (0);
}

void	*malloc_n(size_t size)
{
	size_t	aligned_size;
	t_block	*result;
	t_alloc	type;

handle_addr(size, 10);
ft_putendl(" <-- to allocate | in malloc_n");
	aligned_size = align_size(size, 32);
	if (above_limit(aligned_size))
		return (NULL);
// handle_addr(aligned_size, 10);
// ft_putendl(" <-- to allocate");
	type = find_type_pool(aligned_size);
	result = handle_pool(aligned_size, type);
handle_addr((size_t)result, 16);
ft_putendl(" <-- final alloc");
	if (!result)
		return (NULL);
	return ((void *)result + sizeof(t_block));
}

void	*malloc(size_t size)
{
	void	*res;

	pthread_mutex_lock(&g_mutex);
	res = malloc_n(size);
	pthread_mutex_unlock(&g_mutex);
	return (res);
}
