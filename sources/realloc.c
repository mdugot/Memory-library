#include "libft_malloc.h"

void *move_alloc(memory_allocation *mem, size_t len, memory_allocation *last, memory_page *page)
{
	size_t copy_len;
	void *ad;

	putstr("move alloc\n");
	ad = do_malloc(len);
	putint_endln((unsigned long long)ad, 16, "move_alloc result : 0x", 1);
	if (mem)
	{
	putint_endln((unsigned long long)len, 10, "new len : ", 1);
	putint_endln((unsigned long long)mem->len, 10, "old len : ", 1);
		putstr("mem\n");
		copy_len = mem->len;
		if (mem->len > len)
			copy_len = len;
	putint_endln((unsigned long long)copy_len, 10, "copy len : ", 1);
		putstr("before copy\n");
		if (ad)
			copy_memory(ad, mem->content, copy_len);
		putstr("delete allocation\n");
		delete_allocation(page, mem, last);
		putstr("end delete page\n");
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
//	if (same_type(mem->len, len) && mem->content + len <= end)
//	{
//		mem->len = len;
//		return mem->content;
//	}
	return move_alloc(mem, len, last, page);
}
