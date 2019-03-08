/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_pool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:37:40 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/08 14:15:15 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

t_block	*find_block_of_ptr(void *ptr, t_alloc *type)
{
	t_block	*tmp;

	if (!ptr)
		return (NULL);
	while (*type <= LARGE_TYPE)
	{
		tmp = g_pool[*type];
		while (tmp)
		{
			if ((char *)tmp + sizeof(t_block) == (char *)ptr)
				return (tmp);
			tmp = tmp->next;
		}
		(*type)++;
	}
	(*type)--;
	return (NULL);
}

t_block	*find_available_chunk(size_t size, t_alloc type, t_block **last)
{
	t_block	*tmp;

	tmp = g_pool[type];
	while (tmp && !(tmp->free && tmp->size >= size))
	{
		*last = tmp;
		tmp = tmp->next;
	}
	return (tmp);
}
