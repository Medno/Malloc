/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:39:52 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/08 14:18:28 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_alloc.h"


void	print_edited_p(t_block *tmp)
{
	if (!tmp)
	{
		ft_putendl("No ptr found");
		return ;
	}
	if (!tmp->free)
		ft_putstr("A:	");
	else
		ft_putstr("F	");
	ft_putstr("Size :	|");
	ft_putnbr(tmp->size);
	ft_putstr("|	Address :	|0x");
	handle_addr((size_t)tmp, 16);
	ft_putstr("|	Prev :	|0x");
	handle_addr((size_t)tmp->prev, 16);
	ft_putstr("|	Next :	|0x");
	handle_addr((size_t)tmp->next, 16);
	ft_putstr("|	Block :	|0x");
	handle_addr((size_t)tmp + sizeof(t_block), 16);
	ft_putstr("| -> |0x");
	handle_addr((size_t)tmp + tmp->size + sizeof(t_block), 16);
	ft_putendl("|");

}

void	print_all_pools(void)
{
	t_block	*tmp;
	t_bucket	*buck;
	int		i;

	i = 0;
	ft_putendl("=========================================================================================================================\n=========================================================================================================================");
	while (i < 3)
	{
		ft_putstr("Pool number : |");
		ft_putnbr(i);
		ft_putstr("| ");
		buck = g_pool[i];
		while (buck)
		{
			tmp = buck->block;
			handle_addr((size_t)buck, 16);
			ft_putendl(" Addr of buck");

			handle_addr((size_t)tmp, 16);
			ft_putendl(" Addr of pool");
			while (tmp)
			{
				if (!tmp->free)
					ft_putstr("A:	");
				else
					ft_putstr("F	");
				ft_putstr("Size :	|");
				ft_putnbr(tmp->size);
				ft_putstr("|	Address :	|0x");
				handle_addr((size_t)tmp, 16);
				ft_putstr("|	Prev :	|0x");
				handle_addr((size_t)tmp->prev, 16);
				ft_putstr("|	Next :	|0x");
				handle_addr((size_t)tmp->next, 16);
				ft_putstr("|	Block :	|0x");
				handle_addr((size_t)tmp + sizeof(t_block), 16);
				ft_putstr("| -> |0x");
				handle_addr((size_t)tmp + tmp->size + sizeof(t_block), 16);
				ft_putendl("|");
				//			ft_putstr("to :		|");
				//			handle_addr((size_t)tmp + sizeof(t_block), 10);
				//			ft_putendl("");
				tmp = tmp->next;
			}
			buck = buck->next;
		}
		i++;
	}
	   handle_addr(sizeof(size_t), 10);
	   ft_putendl("");
	   handle_addr(sizeof(t_block *), 10);
	   ft_putendl("");
	   handle_addr(sizeof(t_free), 10);
	   ft_putendl("");
	ft_putendl("=========================================================================================================================\n=========================================================================================================================");
}



int		print_pool(t_bucket *pool)
{
	size_t		res;
	t_block		*tmp;
	t_bucket	*buck;

	res = 0;
	buck = pool;
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
				ft_putstr(" - ");
				ft_putstr("0x");
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
