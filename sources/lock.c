#include "libft_malloc.h"

void lock()
{
	pthread_mutex_lock(get_mutex());
}

void unlock()
{
	pthread_mutex_unlock(get_mutex());
}
