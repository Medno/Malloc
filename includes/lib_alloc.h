#ifndef LIB_ALLOC_H
#define LIB_ALLOC_H

#include "libft.h"
#include <sys/mman.h>

#define NB_ALLOCATION 100
#define TINY 1024
#define SMALL 4096

typedef uint8_t		t_free;

typedef enum		e_alloc
{
	TINY_TYPE,
	SMALL_TYPE,
	LARGE_TYPE
}					t_alloc;

typedef struct		s_block
{
	size_t			size;
	t_free			free;
	struct s_block	*next;
	struct s_block	*prev;
}					t_block;
/*
typedef struct		s_pool
{
	t_block	*alloc;
	t_block	*freed;
}					t_pool;
*/
t_block				*g_pool[3];

t_block				*alloc_mem(void *start_addr, size_t size);

void				free(void *ptr);
void				*malloc(size_t size);
void				show_alloc_mem();

void				*calloc(size_t count, size_t size);
void				defragment_around(t_block *new_freed);

void				*extend_heap(size_t size, t_alloc type);
void				*handle_pool(size_t size, t_alloc type);
size_t				align_size(size_t size, int round);
t_block				*search_available_chunk(size_t size, t_alloc type);
t_block				*find_last_block(t_block *pool, t_block *cmp);
t_block				*find_block_of_ptr(void *ptr, t_alloc *type);

void				handle_addr(size_t value, int base);
void	print_all_pools(void);
#endif
