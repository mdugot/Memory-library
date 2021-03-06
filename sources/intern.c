#include "libft_malloc.h"

static void	*free_space_at_first(memory_page *page, size_t len)
{
	size_t size;

	if (len > SMALL_ALLOCATION)
		return 0;
	size = get_size(len);
	if (!CP(page))
		return (page->adress + sizeof(memory_page));
	if ((BYTE*)CP(page) - (BYTE*)page->adress - sizeof(memory_page) >= size)
		return ((BYTE*)page->adress + sizeof(memory_page));
	return 0;
}


static void	*search_in_page(memory_page *page, memory_allocation *last, size_t size, memory_allocation **alast)
{
	*alast = last;
	if (last->next)
	{
		if ((size_t)((void*)last->next - get_end(last)) >= size)
		{
			return get_end(last);
		}
		return search_in_page(page, last->next, size, alast);
	}
	else if ((size_t)(get_end_page(page) - get_end(last)) >= size)
			return get_end(last);
	return 0;
}

static void	*search_free_space(memory_page *begin, size_t len, memory_allocation **alast)
{
	size_t size;
	int end;
	memory_page *page;
	void *ad;

	if (len > SMALL_ALLOCATION)
		return 0;
	size = get_size(len);
	end = 0;
	page = begin;
	while (!end)
	{
		*alast = 0;
		if (page->empty_space >= size && CP(page))
		{
			ad = search_in_page(page, CP(page), size, alast);
			if (ad)
			{
				return ad;
			}
		}
		if (page->next)
			page = page->next;
		else
			end = 1;
	}
	return 0;
}

static memory_allocation	*new_allocation(void *ad, size_t len, memory_allocation *last, memory_page *page)
{
	memory_allocation	mem;

//	mem.content = (BYTE*)ad + sizeof(memory_allocation);
	mem.len = len;
	mem.next = 0;
	if (last)
	{
		if (last->next)
			mem.next = last->next;
		last->next = ad;
	}
	else
	{
		mem.next = CP(page);
		page->content = ad;
	}
	page->empty_space -= get_size(len);
	copy_memory(ad, (BYTE*)&mem, sizeof(memory_allocation));
	return ad;
}

memory_allocation	*create_allocation(memory_page *page, size_t len)
{
	void *ad;
	memory_page	*new_page;
	memory_page	*last_page;
	memory_allocation	*last;

	last = 0;
	if (page == 0)
		ad = 0;
	else
	{
		if (!(ad = free_space_at_first(page, len)))
			ad = search_free_space(page, len, &last);
	}
	if (ad == 0)
	{
		last_page = get_last_page(len);
		new_page = new_memory_page(last_page, get_page_size(len), len);
		if (!new_page)
			return 0;
		return CP(new_page);
	}
	return new_allocation(ad, len, last, page);
}

memory_page	*new_memory_page(memory_page *last, size_t size, size_t len)
{
	memory_page page;
	BYTE *ad;

	if (size <= len)
		return 0;
	page.size = size;
	page.empty_space = size;
	page.content = 0;
	page.next = 0;
	page.last = last;
//	logint((unsigned long long)len, 10, "MMAP LEN -------> ", 1);
//	logint((unsigned long long)size, 10, "MMAP SIZE -------> ", 1);
	page.adress = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (page.adress == MAP_FAILED)
		return 0;
	if (last)
		last->next = page.adress;
//	logint((unsigned long long)page.adress, 16, "MMAP RESULT -------> 0x", 1);
//	logint((unsigned long long)sizeof(memory_page), 16, "SIZE OF PAGE -------> ", 1);
	ad = (BYTE*)page.adress + sizeof(memory_page);
//	logint((unsigned long long)ad, 16, "AD -------> 0x", 1);
	new_allocation(ad, len, 0, &page);
	copy_memory((void*)page.adress, (BYTE*)&page, sizeof(memory_page));
	set_last_page(len, page.adress);
//	logint((unsigned long long)page.content, 16, "PAGE CONTENT 1 -------> 0x", 1);
	return page.adress;
}
