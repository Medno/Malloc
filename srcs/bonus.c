/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:36:30 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/06 16:38:28 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*result;
	size_t	size_to_bzero;

	pthread_mutex_lock(&g_mutex);
ft_putendl("Before calloc");
//print_all_pools();
	result = malloc_n(count * size);
	size_to_bzero = size == 0 ? 32 : size;
	if (result)
		ft_bzero(result, count * size_to_bzero);
//print_all_pools();
ft_putendl("After calloc");
	pthread_mutex_unlock(&g_mutex);
	return (result);
}

void	*reallocf(void *ptr, size_t size)
{
	void	*res;

ft_putendl("Before reallocf");
	res = realloc(ptr, size);
	if (!res && ptr)
		free(ptr);
ft_putendl("After reallocf");
	return (res);
}

size_t	malloc_size(void *ptr)
{
	t_alloc	type;
	t_block	*tmp;

	tmp = find_block_of_ptr(ptr, &type, NULL);
	if (tmp)
		return (tmp->size);
	return (0);
}

size_t	malloc_good_size(size_t size)
{
	return (align_size(size, 32));
}

t_block	*defragment_around(t_block *new_freed)
{
	if (new_freed && new_freed->next && new_freed->next->free)
	{
		new_freed->size += new_freed->next->size + sizeof(t_block);
		new_freed->next = new_freed->next->next;
		if (new_freed->next)
			new_freed->next->prev = new_freed;
	}
	return (new_freed);
}
