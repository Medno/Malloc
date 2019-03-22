/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desalloc_buckets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:35:35 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/22 09:50:18 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

static int	bucket_is_empty(t_bucket *buck)
{
	return (buck && buck->block && !(buck->block->next));
}

void		desallocate_large(t_alloc type, t_bucket *buck, t_block *found)
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

static int	count_empty_buckets_in_pool(t_alloc type)
{
	t_bucket	*pool;
	int			nb_of_empty;

	pool = g_pool[type];
	nb_of_empty = 0;
	while (pool)
	{
		if (bucket_is_empty(pool))
			nb_of_empty++;
		pool = pool->next;
	}
	return (nb_of_empty);
}

void		check_empty_buckets(t_bucket *buck, t_alloc type)
{
	size_t	buck_size;
	int		nb_of_empty;

	if (bucket_is_empty(buck))
	{
		nb_of_empty = count_empty_buckets_in_pool(type);
		if (nb_of_empty > 1)
		{
			buck_size = align_size(sizeof(t_bucket), ALIGN);
			if (buck->prev)
				buck->prev->next = buck->next;
			else
				g_pool[type] = buck->next;
			if (buck->next)
				buck->next->prev = buck->prev;
			if ((munmap(buck, buck->block->size + sizeof(t_block) + buck_size)) == -1)
				ft_putendl_fd("Error unmapping memory", 2);
		}
	}
}
