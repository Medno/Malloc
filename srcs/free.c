/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:35:35 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/06 16:38:18 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

void	free_n(void *ptr)
{
	t_block	*found;
	t_alloc	type;

	type = TINY_TYPE;
	found = find_block_of_ptr(ptr, &type);
	if (!found)
		return ;
	found->free = 1;
	if (type == LARGE_TYPE)
	{
		if (found->next)
			found->next->prev = found->prev;
		if (!found->prev)
			g_pool[type] = (found->next) ? found->next : NULL;
		else
			found->prev->next = found->next;
		found->next = NULL;
		found->prev = NULL;
		if ((munmap(found, align_size(found->size + sizeof(t_block), 16)))
				== -1)
			ft_putendl_fd("Error unmapping memory", 2);
		return ;
	}
	if (found->prev && found->prev->free)
		found = defragment_around(found->prev);
	if (found)
		defragment_around(found);
	return ;
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
handle_addr((size_t)ptr, 16);
ft_putendl(" <-- Before free");
print_all_pools();
	free_n(ptr);
//print_all_pools();
ft_putendl("After free");
	pthread_mutex_unlock(&g_mutex);
}
