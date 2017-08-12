#include "libft_malloc.h"

static void delete_allocation(memory_page *page, memory_allocation *mem, memory_allocation *last)
{
	if (!last)
		page->content = mem->next;
	else
		last->next = mem->next;
}

static int	free_allocation(memory_page *page, memory_allocation *mem, void *ad, memory_allocation *last)
{
	if (!mem)
		return 0;
	if (mem->content == ad)
	{
		delete_allocation(page, mem, last);
		return 1;
	}
	return free_allocation(page, mem->next, ad, mem);
}

int	free_page(void* ad, memory_page *page)
{
	if (!page)
		return 0;
	if (is_in(page, ad) && free_allocation(page, page->content, ad, 0))
		return 1;
	return free_page(page->next, ad);
}
