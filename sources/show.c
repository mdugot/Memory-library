#include "libft_malloc.h"

static void print_memory_head(memory_allocation *mem)
{
	putint((unsigned long long)mem->content, 16, "0x", 1);
	putstr(" - ");
	putint((unsigned long long)mem->content + mem->len, 16, "0x", 1);
	putstr(" : ");
	putint((unsigned long long)mem->len, 10, "", 1);
	if (mem->len <= 1)
		putstr(" octet\n");
	else
		putstr(" octets\n");
}

void	show_alloc_memory(memory_allocation* mem)
{
	if (!mem)
		return;
	print_memory_head(mem);
	show_alloc_memory(mem->next);
}

void	show_alloc_page(memory_page* begin, char *type)
{
	memory_page *page;

	page = begin;
	while (page)
	{
		putstr(type);
		putstr(" : ");
		putint_endln((unsigned long long)page->adress, 16, "0x", 1);
		show_alloc_memory(page->content);
		page = page->next;
		//show_alloc_page(page->next, type);
	}
}

int	dump_alloc_page(void *ad, memory_page* page, char *type)
{
	memory_allocation *mem;

	mem = find_in_page(ad, page, 0, 0);
	if (mem)
	{
		logint((unsigned long long)sizeof(memory_page), 10, "size of page = ", 1);
		logint((unsigned long long)sizeof(memory_allocation), 10, "size of alloc = ", 1);
		logint((unsigned long long)page, 16, "page = 0x", 1);
		logint((unsigned long long)mem, 16, "alloc = 0x", 1);
		logint((unsigned long long)mem->len, 10, "len = ", 1);
		logint((unsigned long long)mem->content, 16, "adress = 0x", 1);
		putstr(type);
		putstr(" : ");
		print_memory_head(mem);
//		log("dump content\n");
		dump_content((unsigned char*)mem->content, mem->len);
//		log("end dump content\n");
		return 1;
	}
	return 0;
}
