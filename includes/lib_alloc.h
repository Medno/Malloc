#ifndef LIB_ALLOC_H
#define LIB_ALLOC_H

#include "libft.h"
#include <sys/mman.h>

#define NB_ALLOCATION 100

#define TINY 4 * NB_ALLOCATION
#define SMALL 256 * NB_ALLOCATION

enum			e_alloc
{
	TINY_TYPE,
	SMALL_TYPE,
	LARGE_TYPE
};

typedef struct s_block	t_block;
typedef enum e_alloc	t_alloc;

struct	s_block
{
	size_t	size;
	t_block	*next;
	t_block	*prev;
};

typedef struct	s_pool
{
	t_block	*alloc;
	t_block	*freed;
}				t_pool;

t_pool			g_pool[3];

void			*alloc_mem(void *start_addr, size_t size);

void			*malloc(size_t size);
void	*extend_heap(size_t size, t_alloc type);
void	*handle_pool(size_t size, t_alloc type);
size_t	align_size(size_t size, int round);
t_block	*search_available_chunk(size_t size, t_alloc type);
t_block	*find_last_block(t_block *pool);

#endif
