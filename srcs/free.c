/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:35:35 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/16 15:57:18 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

void	desallocate_large(t_alloc type, t_bucket *buck, t_block *found)
{
	size_t	buck_size;

	buck_size = align_size(sizeof(t_bucket), ALIGN);
	if (g_pool[type] == buck)
		g_pool[type] = (buck->next) ? buck->next : NULL;
	else
		buck->prev->next = buck->next;
	if (buck->next)
		buck->next->prev = buck->prev;
	buck->next = NULL;
	buck->prev = NULL;
	if ((munmap(buck, found->size + sizeof(t_block) + buck_size)) == -1)
		ft_putendl_fd("Error unmapping memory", 2);
	return ;
}

void	free_n(void *ptr)
{
	t_bucket	*bucket;
	t_block		*found;
	t_alloc		type;

	type = TINY_TYPE;
	bucket = g_pool[type];
	found = find_block_of_ptr(ptr, &type, &bucket);
	if (!found)
		return ;
	if (type == LARGE_TYPE)
		desallocate_large(type, bucket, found);
	else
	{
		found->free = 1;
		if (found->prev && found->prev->free)
			found = defragment_around(found->prev);
		if (found)
			defragment_around(found);
	}
	return ;
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	free_n(ptr);
	pthread_mutex_unlock(&g_mutex);
}
