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
	while (1)
	{
		if (!page)
			return;
		putstr(type);
		putstr(" : ");
		putint_endln((unsigned long long)page->adress, 16, "0x", 1);
		show_alloc_memory(page->content);
		page = page->next;
		//show_alloc_page(page->next, type);
	}
}

/*int	dump_alloc_memory(void *ad, memory_allocation* mem, char *type)
{

	if (!mem)
		return 0;
	if (ad >= mem->content && ad < mem->content + mem->len)
	{
		putstr(type);
		putstr(" : ");
		print_memory_head(mem);
		dump_content(mem->content, mem->len);
		return 1;
	}
	return dump_alloc_memory(ad, mem->next, type);
}*/

int	dump_alloc_page(void *ad, memory_page* page, char *type)
{
	memory_allocation *mem;

	mem = find_in_page(ad, page, 0, 0);
	if (mem)
	{
		putstr(type);
		putstr(" : ");
		print_memory_head(mem);
		dump_content(mem->content, mem->len);
		return 1;
	}
	return 0;

/*	if (!page)
		return 0;
	if (is_in(page, ad) && dump_alloc_memory(ad, page->content, type))
		return 1;
	return dump_alloc_page(ad, page->next, type);*/
}
