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
	return CM(m) + m->len;
}

void *get_end_page(memory_page *p)
{
	return (BYTE*)p->adress + p->size;
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

void set_last_page(size_t len, memory_page *page)
{
	memory_annuary *annuary;

	annuary =  get_annuary();
	if (len <= TINY_ALLOCATION)
		annuary->last_tiny = page;
	else if (len <= SMALL_ALLOCATION)
		annuary->last_small = page;
	else
		annuary->last_large = page;
}

memory_page	*get_last_page(size_t len)
{
	memory_annuary *annuary;

	annuary =  get_annuary();
	if (len <= TINY_ALLOCATION)
		return annuary->last_tiny;
	if (len <= SMALL_ALLOCATION)
		return annuary->last_small;
	return annuary->last_large;
}

int	same_type(size_t lena, size_t lenb)
{
	if (lena <= TINY_ALLOCATION && lenb <= TINY_ALLOCATION)
		return 1;
	if (lena > SMALL_ALLOCATION && lenb > SMALL_ALLOCATION)
		return 1;
	if (lena <= SMALL_ALLOCATION && lenb <= SMALL_ALLOCATION)
	{
		if (lena > TINY_ALLOCATION && lenb > TINY_ALLOCATION)
			return 1;
	}
	return 0;
}

BYTE *content(BYTE *ad, size_t len)
{
	return ad + len;
}

int get_number_page(memory_page *page, int n)
{
	if (!page)
		return n;
	return get_number_page(page->next, n+1);
}

int is_first_page(memory_page *page)
{
	memory_annuary *annuary;

	annuary = get_annuary();
	if (annuary->tiny == page)
		return 1;
	if (annuary->small == page)
		return 1;
	if (annuary->large == page)
		return 1;
	return 0;
}
