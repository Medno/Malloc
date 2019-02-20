#include "lib_alloc.h"

void	assign_pool(t_block **pool, t_block *new)
{
	*pool = new;
}

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
print_all_pools();
handle_addr((size_t)found->prev, 16);
ft_putendl(" <- freed prev");
handle_addr((size_t)found->next, 16);
ft_putendl(" <- freed next");
handle_addr(g_pool[2]->size, 10);
ft_putendl(" <- Poolsize");
handle_addr((size_t)g_pool[2]->next, 16);
ft_putendl(" <- pool next");
handle_addr((size_t)found->next->prev, 16);
ft_putendl(" <- freed->next prev");
handle_addr(found->next->size, 10);
ft_putendl(" <- freed->next size");
//		delete_from_pool();

		if (!found->prev)
		{
			ft_putendl("Pas de prev");
			g_pool[type] = (found->next);
			g_pool[type]->prev = NULL;
		}
		else
		{
			ft_putendl("Toto");
			found->prev->next = found->next;
		}
		found->next = NULL;
		found->prev = NULL;

handle_addr((size_t)found->size + sizeof(t_block), 10);
ft_putendl(" <- size to desallocate");
handle_addr((size_t)found, 16);
ft_putstr(" - ");
handle_addr((size_t)found + sizeof(t_block) + found->size, 16);
ft_putendl(" <- desallocate");
		if ((munmap(found, found->size + sizeof(t_block))) == -1)
			ft_putendl_fd("Error unmapping memory", 2);
handle_addr(sizeof(t_block), 10);
ft_putendl(" <- t_block size");
handle_addr(g_pool[2]->size, 16);
ft_putendl(" <- Pool size");
handle_addr((size_t)g_pool[2], 16);
ft_putendl(" <- Pool updated");
handle_addr((size_t)found, 16);
ft_putendl(" <- Large type freed");
		return ;
	}
	defragment_around(found);
	return ;
}

void	free(void *ptr)
{
	ft_putendl("Before free");
print_all_pools();
	free_n(ptr);
print_all_pools();
	ft_putendl("After free");
}
