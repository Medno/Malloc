/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_pool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:37:40 by pchadeni          #+#    #+#             */
/*   Updated: 2019/02/25 16:37:53 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

t_block	*find_block_of_ptr(void *ptr, t_alloc *type)
{
	t_block	*result;

	result = NULL;
	if (!ptr)
		return (NULL);
	while (*type <= LARGE_TYPE && !result)
	{
		result = find_last_block(g_pool[*type],
				(t_block *)(ptr - sizeof(t_block)));
		if (!result || (t_block *)(ptr - sizeof(t_block)) != result)
			result = NULL;
		(*type)++;
	}
	if (result && !result->next &&
			(t_block *)(ptr - sizeof(t_block)) != result)
		return (NULL);
	(*type)--;
	return (result);
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

t_block	*find_last_block(t_block *pool, t_block *cmp)
{
	t_block	*tmp;

	tmp = pool;
	while (tmp && tmp->next)
	{
		if (cmp && (tmp->next > cmp || tmp >= cmp))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}
