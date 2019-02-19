#include "lib_alloc.h"

t_block	*alloc_mem(void *start_addr, size_t size)
{
	t_block	*tmp;

	if ((tmp = mmap(start_addr, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (tmp);
}

size_t	align_size(size_t size, int round)
{
	if (!size)
		return (round);
	return ((((size - 1) / round) * round) + round);
}

t_alloc	find_type_pool(size_t size)
{
	if (size <= TINY)
		return (TINY_TYPE);
	else if (size <= SMALL)
		return (SMALL_TYPE);
	return (LARGE_TYPE);
}

void	print_all_pools(void)
{
	t_block	*tmp;
	int		i;

	i = 0;
	ft_putendl("==================================");
	ft_putendl("==================================");
	while (i < 3)
	{
		ft_putstr("Pool number : |");
		ft_putnbr(i);
		ft_putendl("|");
		tmp = g_pool[i].alloc;
		while (tmp)
		{
			ft_putstr("Block allocated:\n");
			ft_putstr("Size :		|");
			ft_putnbr(tmp->size);
			ft_putendl("|");
			ft_putstr("Address :	|0x");
			handle_addr((size_t)tmp, 16);
			ft_putendl("|");
			ft_putstr("Prev :		|0x");
			handle_addr((size_t)tmp->prev, 16);
			ft_putendl("|");
			ft_putstr("Next :		|0x");
			handle_addr((size_t)tmp->next, 16);
			ft_putendl("|");
			ft_putstr("From -> to :		|0x");
			handle_addr((size_t)tmp + sizeof(t_block), 16);
			ft_putstr("| -> |");
			handle_addr((size_t)tmp + tmp->size, 16);
			ft_putendl("|");
			tmp = tmp->next;
			//Print the interval
		}
		tmp = g_pool[i].freed;
		while (tmp)
		{
			ft_putstr("Block freed:\n");
			ft_putstr("Size :		|");
			ft_putnbr(tmp->size);
			ft_putendl("|");
			ft_putstr("Address :	|0x");
			handle_addr((size_t)tmp, 16);
			ft_putendl("|");
			ft_putstr("Prev :		|0x");
			handle_addr((size_t)tmp->prev, 16);
			ft_putendl("|");
			ft_putstr("Next :		|0x");
			handle_addr((size_t)tmp->next, 16);
			ft_putendl("|");
			tmp = tmp->next;
		}
		i++;
	}
	ft_putendl("==================================");
	ft_putendl("==================================");
}

void	*calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (result)
		ft_bzero(result, count * size);
	return (result);
}

void	*malloc(size_t size)
{
	size_t	aligned_size;
	void	*result;
	t_alloc	type;

	aligned_size = align_size(size, 4);
	type = find_type_pool(aligned_size);
	if (type == LARGE_TYPE)
		result = extend_heap(aligned_size, type);
	else
		result = handle_pool(aligned_size, type);
	return ((void *)((char *)result + sizeof(t_block)));
}
