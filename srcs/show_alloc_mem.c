/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:39:52 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/16 16:29:09 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

int		print_pool(t_bucket *buck, uint8_t free)
{
	size_t		res;
	t_block		*tmp;

	res = 0;
	while (buck)
	{
		tmp = buck->block;
		while (tmp)
		{
			if (free || !tmp->free)
			{
				res += tmp->size;
				ft_putstr("0x");
				handle_addr((size_t)tmp + sizeof(t_block), 16);
				ft_putstr(" - 0x");
				handle_addr((size_t)tmp + sizeof(t_block) + tmp->size, 16);
				ft_putstr(" : ");
				handle_addr(tmp->size, 10);
				ft_putendl(" octets");
			}
			tmp = tmp->next;
		}
		buck = buck->next;
	}
	return (res);
}

void	show_alloc_mem(void)
{
	size_t		size;
	uint8_t		i;
	t_bucket	*tmp;

	i = 0;
	size = 0;
	pthread_mutex_lock(&g_mutex);
	while (i < 3)
	{
		if (!i)
			ft_putstr("TINY : ");
		if (i == 1)
			ft_putstr("SMALL : ");
		if (i == 2)
			ft_putstr("LARGE : ");
		tmp = g_pool[i];
		ft_putstr("0x");
		handle_addr((size_t)tmp, 16);
		ft_putchar('\n');
		size += print_pool(tmp, 0);
		i++;
	}
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putendl(" octets");
	pthread_mutex_unlock(&g_mutex);
}

void	show_alloc_mem_hex(void)
{
	size_t		size;
	uint8_t		i;
	t_bucket	*tmp;

	i = 0;
	size = 0;
	pthread_mutex_lock(&g_mutex);
	while (i < 3)
	{
		if (!i)
			ft_putstr("TINY : ");
		if (i == 1)
			ft_putstr("SMALL : ");
		if (i == 2)
			ft_putstr("LARGE : ");
		tmp = g_pool[i];
		ft_putstr("0x");
		handle_addr((size_t)tmp, 16);
		ft_putchar('\n');
		size += print_pool(tmp, 1);
		i++;
	}
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putendl(" octets");
	pthread_mutex_unlock(&g_mutex);

}
