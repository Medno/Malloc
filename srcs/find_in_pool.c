/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_pool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:37:40 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/16 15:57:26 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

t_block	*find_available_chunk(size_t size, t_alloc type, t_bucket **last)
{
	t_bucket	*bucket_tmp;
	t_block		*tmp;

	bucket_tmp = g_pool[type];
	*last = bucket_tmp;
	tmp = NULL;
	while (bucket_tmp && (!tmp || (tmp && !(tmp->free && tmp->size >= size))))
	{
		tmp = bucket_tmp->block;
		while (tmp && !(tmp->free && tmp->size >= size))
			tmp = tmp->next;
		if (!(bucket_tmp->next))
			*last = bucket_tmp;
		bucket_tmp = bucket_tmp->next;
	}
	return (tmp);
}

t_block	*find_block_of_ptr(void *ptr, t_alloc *type, t_bucket **buck)
{
	t_block	*tmp;

	if (!ptr)
		return (NULL);
	while (*type <= LARGE_TYPE)
	{
		*buck = g_pool[*type];
		while (*buck)
		{
			if ((uintptr_t)*buck < (uintptr_t)ptr && (*buck)->end > ptr)
			{
				tmp = (*buck)->block;
				while (tmp)
				{
					if ((uintptr_t)ptr == (uintptr_t)tmp + sizeof(t_block))
						return (tmp);
					tmp = tmp->next;
				}
				return (NULL);
			}
			(*buck) = (*buck)->next;
		}
		(*type)++;
	}
	return (NULL);
}
