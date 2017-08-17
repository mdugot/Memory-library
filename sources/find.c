#include "libft_malloc.h"

static memory_allocation*	find_allocation(memory_page *page, memory_allocation *mem, void *ad, memory_allocation **alast, unsigned long long deep)
{
	if (!mem)
		return 0;
	if (mem->content == ad)
		return mem;
	if (alast)
		*alast = mem;
	return find_allocation(page, mem->next, ad, alast, deep+1);
}


memory_allocation *find_in_page(void *ad, memory_page *begin, memory_allocation **alast, memory_page **apage)
{
	memory_page *page;
	memory_allocation *result;

	page = begin;
	if (!page)
		return 0;
	if (alast)
		*alast = 0;
	unsigned long long n = 0;
	while (page)
	{
		if (is_in(page, ad))
		{
			result = find_allocation(page, page->content, ad, 0, 0);
			if (result)
			{
				if (apage)
					*apage = page;
				return result;
			}
		}
		page = page->next;
		n++;
	}
	return 0;
}
