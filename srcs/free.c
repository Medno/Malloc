/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:35:35 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/22 09:49:58 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

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
		check_empty_buckets(bucket, type);
	}
	return ;
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	free_n(ptr);
	pthread_mutex_unlock(&g_mutex);
}
