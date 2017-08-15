#include "libft_malloc.h"

void delete_allocation(memory_page *page, memory_allocation *mem, memory_allocation *last)
{
	page->empty_space += get_size(mem->len);
	if (!last)
		page->content = mem->next;
	else
		last->next = mem->next;
	clean_page(page);
}

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
}

void clean_page(memory_page *page)
{
	if (!page || page->content)
		return;
	*(page->origin) = page->next;
	munmap(page->adress, page->size);
}
