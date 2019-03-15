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

t_block	*find_block_of_ptr(void *ptr, t_alloc *type, t_bucket **buck)
{
	t_block	*tmp;

	if (!ptr)
		return (NULL);
	tmp = NULL;
	*buck = g_pool[*type];
	ft_putendl("Start searching for the corresponding Block");
handle_addr((uintptr_t)ptr, 16);
ft_putendl(" <-- add of ptr");
	while (*type <= LARGE_TYPE)
	{
		*buck = g_pool[*type];
		while (*buck && (uintptr_t)(*buck) < (uintptr_t)ptr)
		{
			handle_addr((uintptr_t)*buck, 16);
			ft_putendl(" <-- Begin buck during search");
			handle_addr((uintptr_t)(*buck)->next, 16);
			ft_putendl(" <-- Begin->next buck during search");

			if ((!(*buck)->next)
			|| ((*buck)->next && (uintptr_t)ptr > (uintptr_t)(*buck)->next))
			{
				tmp = (*buck)->block;
				while (tmp)
				{
					handle_addr((uintptr_t)tmp, 16);
					ft_putendl(" <-- Search the add of block ");
					if ((uintptr_t)ptr == (uintptr_t)tmp + sizeof(t_block))
						return (tmp);
					tmp = tmp->next;
				}
			}
			handle_addr((uintptr_t)*buck, 16);
			ft_putendl(" <-- add of buck during search");
			*buck = (*buck)->next;
		}
		(*type)++;
	}
	handle_addr((uintptr_t)*buck, 16);
	ft_putendl(" <-- add of buck after search");
	(*type)--;

	if (!*buck)
		return (NULL);
/*
	Retirer l'ancien pointeur de la liste et retourner le nouveau crée !
*/


	ft_putendl(" <-- d");
	return (NULL);
	// while (*type <= LARGE_TYPE && !result)
	// {
	// 	result = find_last_block(g_pool[*type],
	// 			(t_block *)(ptr - sizeof(t_block)));
	// 	if (!result || (t_block *)(ptr - sizeof(t_block)) != result)
	// 		result = NULL;
	// 	(*type)++;
	// }
	// if (result && !result->next &&
	// 		(t_block *)(ptr - sizeof(t_block)) != result)
	// 	return (NULL);
	// (*type)--;
	// return (result);
}

t_block	*find_available_chunk(size_t size, t_alloc type, t_bucket **last)
{
	t_block	*tmp;
	t_bucket	*bucket_tmp;

	bucket_tmp = g_pool[type];
	tmp = NULL;
	while (bucket_tmp)
	{
		tmp = bucket_tmp->block;
		while (tmp && !(tmp->free && tmp->size >= size))
		{
			*last = bucket_tmp;
			tmp = tmp->next;
		}
		bucket_tmp = bucket_tmp->next;
	}
	return (tmp);
}
