#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

#include <pthread.h>
# include "memory_annuary.h"

void *malloc(size_t len);
void	show_alloc_mem();
int	dump_alloc_mem(void *ad);
void	free(void *ad);
void	*realloc(void *ad, size_t size);

#endif
