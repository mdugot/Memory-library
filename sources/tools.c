#include "libft_malloc.h"

size_t get_size(size_t len)
{
	return (len + sizeof(memory_allocation));
}

size_t get_first_size(size_t len)
{
	return (len + sizeof(memory_allocation) + sizeof(memory_page));
}

void *get_end(memory_allocation *m)
{
	return m->content + m->len;
}

void *get_end_page(memory_page *p)
{
	return p->adress + p->size;
}

static size_t	up_round(size_t len)
{
	size_t tmp;
	memory_annuary *annuary;

	annuary = get_annuary();
	if (len % annuary->page_size == 0)
		return len;
	tmp = len / annuary->page_size;
	return annuary->page_size *(tmp + 1);
}

size_t	get_page_size(size_t len)
{
	memory_annuary *annuary;

	annuary = get_annuary();
	if (len <= TINY_ALLOCATION)
		return TINY_PAGE * annuary->page_size;
	if (len <= SMALL_ALLOCATION)
		return SMALL_PAGE * annuary->page_size;
	return up_round(get_first_size(len));
}

memory_page	*get_last_page(memory_page *page)
{
	if (!page)
		return 0;
	if (!page->next)
		return page;
	return get_last_page(page->next);
}
