#include "libft_malloc.h"

static void	*search_free_space(memory_page *page, memory_allocation *last, size_t len, memory_allocation **alast)
{
	size_t size;

	size = get_size(len);
	*alast = last;
	if (last->next)
	{
		if ((size_t)(last->next->content - get_end(last)) > size)
			return get_end(last) + 1;
		return search_free_space(page, last->next, len, alast);
	}
	else
	{
		if ((size_t)(get_end_page(page) - get_end(last)) > size)
			return get_end(last) + 1;
		if (page->next)
			return search_free_space(page->next, page->next->content, len, alast);
	}
	*alast = 0;
	return 0;
}

static memory_allocation	*new_allocation(void *ad, size_t len, memory_allocation *last)
{
	memory_allocation	mem;

	mem.content = ad + sizeof(memory_allocation);
	mem.len = len;
	mem.next = 0;
	if (last)
	{
		if (last->next)
			mem.next = last->next;
		last->next = ad;
	}
	copy_memory(ad, (char*)&mem, sizeof(memory_allocation));
	clean_memory(mem.content, mem.len);
	return ad;
}

memory_allocation	*create_allocation(memory_page *page, size_t len)
{
	void *ad;
	memory_page	*new_page;
	memory_allocation	*last;

	if (page == 0)
		ad = 0;
	else
		ad = search_free_space(page, page->content, len, &last);
	if (ad == 0)
	{
		new_page = new_memory_page(get_last_page(page), get_page_size(len), len);
		return new_page->content;
	}
	return new_allocation(ad, len, last);
}

memory_page	*new_memory_page(memory_page *last, size_t size, size_t len)
{
	memory_page page;
	void *ad;

	putint_endln((unsigned long long)last, 16, "0x", 1);
	page.size = size;
	page.next = 0;
	page.adress = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (last)
		last->next = page.adress;
	ad = page.adress + sizeof(memory_page);
	page.content = new_allocation(ad, len, 0);
	copy_memory(page.adress, (char*)&page, sizeof(memory_page));
	return page.adress;
}
