#include "libft_malloc.h"

void *move_alloc(memory_allocation *mem, size_t len, memory_allocation *last, memory_page *page)
{
	size_t copy_len;
	void *ad;

	ad = do_malloc(len);
	if (mem)
	{
		copy_len = mem->len;
		if (mem->len > len)
			copy_len = len;
		if (ad)
			copy_memory(ad, mem->content, copy_len);
		delete_allocation(page, mem, last);
	}
	return ad;
}

void *realloc_page(void *ad, size_t len, memory_page *begin)
{
	memory_allocation *mem;
	memory_allocation *last;
	memory_page *page;
	size_t size;
	void *end;

	size = get_size(len);
	mem = find_in_page(ad, begin, &last, &page);
	if (!mem)
		return 0;
	if (mem->next)
		end = mem->content;
	else
		end = get_end_page(page);
	if (same_type(mem->len, len) && mem->content + len <= end)
	{
		mem->len = len;
		return mem->content;
	}
	return move_alloc(mem, len, last, page);
}
