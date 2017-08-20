#include "libft_malloc.h"

void copy_memory(BYTE* ad, BYTE *mem, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		ad[i] = mem[i];
		i++;
	}
}

void clean_memory(BYTE* ad, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		ad[i] = 0;
		i++;
	}
}

int is_in(memory_page* page, void *ad)
{
	if (!page->content)
		return 0;
	if ((BYTE*)ad < (BYTE*)page->content)
		return 0;
	if ((BYTE*)ad >= (BYTE*)page->adress + page->size)
		return 0;
	return 1;
}
