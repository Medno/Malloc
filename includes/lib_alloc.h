/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_alloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 16:30:12 by pchadeni          #+#    #+#             */
/*   Updated: 2019/03/16 16:30:27 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_ALLOC_H
# define LIB_ALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <pthread.h>

# define ALIGN			16
# define NB_ALLOCATION	100
# define TINY			256
# define SMALL			4096

typedef uint8_t		t_free;
extern pthread_mutex_t		g_mutex;

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

typedef struct		s_bucket
{
	t_block			*block;
	void			*end;
	struct s_bucket	*next;
	struct s_bucket	*prev;
}					t_bucket;

t_bucket				*g_pool[3];

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);

void				show_alloc_mem_hex(void);
void				*calloc(size_t count, size_t size);
void				*reallocf(void *ptr, size_t size);
t_block				*defragment_around(t_block *new_freed);
size_t				malloc_size(void *ptr);
size_t				malloc_good_size(size_t size);

t_bucket			*alloc_mem(void *start_addr, size_t size);
t_block				*handle_pool(size_t size, t_alloc type);
t_block				*split_block(size_t size, t_block *to_split);
size_t				align_size(size_t size, int round);
size_t				align_header(void);
void				handle_addr(size_t value, int base);

t_block				*find_available_chunk(size_t s, t_alloc t, t_bucket **l);
t_block				*find_block_of_ptr(void *ptr, t_alloc *t, t_bucket **b);
t_alloc				find_type_pool(size_t size);

void				free_n(void *ptr);
void				*malloc_n(size_t size);
void				*realloc_n(void *ptr, size_t size);

void				check_empty_buckets(t_bucket *buck, t_alloc type);
void				desallocate_large(t_alloc t, t_bucket *b, t_block *f);
#endif
