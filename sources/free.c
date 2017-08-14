#include "libft_malloc.h"

void delete_allocation(memory_page *page, memory_allocation *mem, memory_allocation *last)
{
	page->empty_space += get_size(mem->len);
	if (!last)
		page->content = mem->next;
	else
		last->next = mem->next;
}

/*static int	free_allocation(memory_page *page, memory_allocation *mem, void *ad, memory_allocation *last)
{
	if (!mem)
		return 0;
	if (mem->content == ad)
	{
		delete_allocation(page, mem, last);
		return 1;
	}
	return free_allocation(page, mem->next, ad, mem);
}*/

int	free_page(void* ad, memory_page *begin)
{
	memory_page *page;
	memory_allocation *mem;
	memory_allocation *last;

	mem = find_in_page(ad, begin, &last, &page);
	if (mem)
	{
		delete_allocation(page, mem, last);
		return 1;
	}
	return 0;

/*	page = begin;
	while (1)
	{
		if (!page)
			return 0;
		if (is_in(page, ad) && free_allocation(page, page->content, ad, 0))
			return 1;
		page = page->next;
	}*/
}

void clean_page(memory_page **origin)
{
	memory_page* page;
	memory_page* next;
	memory_page** next_origin;

	page = *origin;
	if (!page)
		return;
	next = page->next;
	next_origin = &(page->next);
	if (!page->content)
	{
		if (munmap(page->adress, page->size) == 0)
		{
			next_origin = origin;
			*origin = next;
		}
	}
	clean_page(next_origin);
}
