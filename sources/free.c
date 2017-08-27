#include "libft_malloc.h"

void delete_allocation(memory_page *page, memory_allocation *mem, memory_allocation *last)
{
	page->empty_space += get_size(mem->len);
	if (!last)
		CP(page) = mem->next;
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

void clean_annuary(memory_page *page)
{
	memory_annuary *annuary;
	
	annuary = get_annuary();
	if (annuary->last_tiny == page)
		annuary->last_tiny = page->last;
	if (annuary->last_small == page)
		annuary->last_small = page->last;
	if (annuary->last_large == page)
		annuary->last_large = page->last;
	if (annuary->tiny == page)
		annuary->tiny = page->next;
	if (annuary->small == page)
		annuary->small = page->next;
	if (annuary->large == page)
		annuary->large = page->next;
}

void clean_page(memory_page *page)
{
	if (!page || CP(page) || is_first_page(page))
		return;
	if (page->next)
		page->next->last = page->last;
	if (page->last)
		page->last->next = page->next;
	clean_annuary(page);
	plog("UNMAP\n");
	munmap(page->adress, page->size);
}
