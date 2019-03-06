/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:39:52 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/06 13:47:53 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"

int		print_pool(t_block *pool, uint8_t free)
{
	size_t	res;
	t_block	*tmp;

	tmp = pool;
	res = 0;
	while (tmp)
	{
		if (!tmp->free || free)
		{
			res += tmp->size;
			ft_putstr("0x");
			handle_addr((size_t)tmp + sizeof(t_block), 16);
			ft_putstr(" - ");
			ft_putstr("0x");
			handle_addr((size_t)tmp + sizeof(t_block) + tmp->size, 16);
			ft_putstr(" : ");
			handle_addr(tmp->size, 10);
			ft_putendl(" octets");
		}
		tmp = tmp->next;
	}
	return (res);
}

void	show_alloc_mem(void)
{
	size_t	size;

	size = 0;
	ft_putstr("TINY : ");
	ft_putstr("0x");
	handle_addr((size_t)g_pool[0], 16);
	ft_putchar('\n');
	size += print_pool(g_pool[0], 0);
	ft_putstr("SMALL : ");
	ft_putstr("0x");
	handle_addr((size_t)g_pool[1], 16);
	ft_putchar('\n');
	size += print_pool(g_pool[1], 0);
	ft_putstr("LARGE : ");
	ft_putstr("0x");
	handle_addr((size_t)g_pool[2], 16);
	ft_putchar('\n');
	size += print_pool(g_pool[2], 0);
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putendl(" octets");
}

void	show_alloc_mem_hex(void)
{
	size_t	size;

	size = 0;
	ft_putstr("TINY : ");
	ft_putstr("0x");
	handle_addr((size_t)g_pool[0], 16);
	ft_putchar('\n');
	size += print_pool(g_pool[0], 1);
	ft_putstr("SMALL : ");
	ft_putstr("0x");
	handle_addr((size_t)g_pool[1], 16);
	ft_putchar('\n');
	size += print_pool(g_pool[1], 1);
	ft_putstr("LARGE : ");
	ft_putstr("0x");
	handle_addr((size_t)g_pool[2], 16);
	ft_putchar('\n');
	size += print_pool(g_pool[2], 1);
	ft_putstr("Total : ");
	ft_putnbr(size);
	ft_putendl(" octets");
}
