#include "libft_malloc.h"

void copy_memory(char* ad, char *mem, size_t len)
{
	size_t i;

	i = 0;
	while (i < len - 1)
	{
		putint_endln((unsigned long long)i, 10, "copy : ", 1);
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

int is_in(memory_page* page, void *ad)
{
	putint_endln((unsigned long long)page, 16, "is in page : 0x", 1);
	if (!page->content)
		return 0;
	if (ad < (void*)page->content)
		return 0;
	if (ad >= (void*)page->adress + page->size)
		return 0;
	return 1;
}
