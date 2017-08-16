#include "libft_malloc.h"

static memory_allocation*	find_allocation(memory_page *page, memory_allocation *mem, void *ad, memory_allocation **alast, unsigned long long deep)
{
	putint_endln(deep, 10, "deep : ", 1);
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
	putstr("search\n");
	unsigned long long n = 0;
	while (page)
	{
		putint_endln(n, 10, "check if in : ", 1);
		if (is_in(page, ad))
		{
			putstr("is in\n");
			result = find_allocation(page, page->content, ad, 0, 0);
			if (result)
			{
				if (apage)
					*apage = page;
				putstr("find\n");
				return result;
			}
		}
		putstr("not in\n");
		page = page->next;
		n++;
	}
	putstr("no find\n");
	return 0;
}
