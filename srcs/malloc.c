/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:36:30 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/16 16:13:51 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

t_bucket		*alloc_mem(void *start_addr, size_t size)
{
	t_bucket	*tmp;

	if ((tmp = mmap(start_addr, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (tmp);
}

t_alloc			find_type_pool(size_t size)
{
	if (size <= TINY)
		return (TINY_TYPE);
	else if (size <= SMALL)
		return (SMALL_TYPE);
	return (LARGE_TYPE);
}

static uint8_t	above_limit(size_t size)
{
	struct rlimit	limit;

	if (getrlimit(RLIMIT_DATA, &limit))
		return (1);
	if (size > limit.rlim_cur || size == 0)
		return (1);
	return (0);
}

void			*malloc_n(size_t size)
{
	size_t	aligned_size;
	t_block	*result;
	t_alloc	type;

	aligned_size = align_size(size, ALIGN);
	if (above_limit(aligned_size))
		return (NULL);
	type = find_type_pool(aligned_size);
	result = handle_pool(aligned_size, type);
	if (!result)
		return (NULL);
	return ((void *)((char *)result + sizeof(t_block)));
}

void			*malloc(size_t size)
{
	void	*res;

	pthread_mutex_lock(&g_mutex);
	res = malloc_n(size);
	pthread_mutex_unlock(&g_mutex);
	return (res);
}
