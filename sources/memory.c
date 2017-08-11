#include "libft_malloc.h"

void copy_memory(char* ad, char *mem, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		ad[i] = mem[i];
		i++;
	}
}

void clean_memory(char* ad, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		ad[i] = 0;
		i++;
	}
}
