/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:35:35 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/08 14:23:01 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

void	free_n(void *ptr)
{
	t_block	*found;
	t_bucket	*bucket;
	t_alloc	type;

ft_putendl("Begin of free");
	type = TINY_TYPE;
	found = find_block_of_ptr(ptr, &type, &bucket);
/*
handle_addr((uintptr_t)ptr, 16);
ft_putendl(" <-- ptr");
handle_addr((size_t)found, 16);
ft_putendl(" <-- ptr found");
print_edited_p(found);
handle_addr(type, 10);
ft_putendl(" <-- corresponding type found");
*/
	if (!found)
		return ;
	found->free = 1;
	if (type == LARGE_TYPE)
	{
		if (g_pool[type] == bucket)
			g_pool[type] = (bucket->next) ? bucket->next : NULL;
		else
			bucket->prev->next = bucket->next;
		bucket->next = NULL;
		bucket->prev = NULL;
		if ((munmap(bucket,
			found->size + sizeof(t_block) + sizeof(t_bucket))) == -1)
			ft_putendl_fd("Error unmapping memory", 2);
ft_putendl("After free");
		return ;
	}
	if (found->prev && found->prev->free)
		found = defragment_around(found->prev);
	if (found)
		defragment_around(found);
// print_all_pools();
ft_putendl("After free");
	return ;
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	free_n(ptr);
// print_all_pools();

	pthread_mutex_unlock(&g_mutex);
}
