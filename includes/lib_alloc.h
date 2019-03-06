#ifndef LIB_ALLOC_H
#define LIB_ALLOC_H

#include "libft.h"
# include <sys/mman.h>
# include <pthread.h>


#define NB_ALLOCATION 100
#define TINY 1024
#define SMALL 4096

typedef uint8_t		t_free;
pthread_mutex_t		g_mutex;


typedef enum		e_alloc
{
	TINY_TYPE,
	SMALL_TYPE,
	LARGE_TYPE
}					t_alloc;

typedef struct		s_block
{
	struct s_block	*next;
	struct s_block	*prev;
	size_t			size;
	t_free			free;
	char			padding[7];
}					t_block;

t_block				*g_pool[3];


void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();

void				*calloc(size_t count, size_t size);
t_block				*defragment_around(t_block *new_freed);
size_t				malloc_size(void *ptr);
size_t				malloc_good_size(size_t size);
void				*reallocf(void *ptr, size_t size);

t_block				*alloc_mem(void *start_addr, size_t size);
t_block				*handle_pool(size_t size, t_alloc type);
size_t				align_size(size_t size, int round);
t_block				*split_block(size_t size, t_block *to_split);

t_block				*find_available_chunk(size_t s, t_alloc t, t_block **l);
t_block				*find_last_block(t_block *pool, t_block *cmp);
t_block				*find_block_of_ptr(void *ptr, t_alloc *type);
t_alloc				find_type_pool(size_t size);


void				free_n(void *ptr);
void				*malloc_n(size_t size);

void				handle_addr(size_t value, int base);
void	print_all_pools(void);
void	print_edited_p(t_block *tmp);
#endif
