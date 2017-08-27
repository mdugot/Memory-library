#include "libft_malloc.h"

static memory_annuary annuary = {0, 0, 0, 0, 0, 0, 0};
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


memory_annuary	*get_annuary()
{
	return &annuary;
}

pthread_mutex_t	*get_mutex()
{
	return &mutex;
}

static void *malloc_on_page(size_t len, memory_page** page)
{
	memory_page *tmp_page;
	memory_allocation *tmp_mem;
	size_t size;

	if (*page == 0)
	{
		size = get_page_size(len);
		tmp_page = new_memory_page(0, size, len);
		if (!tmp_page)
			return 0;
		*page = tmp_page;
		return (CM(CP(tmp_page)));
	}
	tmp_mem = create_allocation(*page, len);
	if (!tmp_mem)
		return 0;
	return CM(tmp_mem);
}

void *do_malloc(size_t len)
{
	if (len == 0)
		return 0;
	if (annuary.page_size == 0)
		annuary.page_size = getpagesize();
	if (len <= TINY_ALLOCATION)
		return malloc_on_page(len, &(annuary.tiny));
	if (len <= SMALL_ALLOCATION)
		return malloc_on_page(len, &(annuary.small));
	return malloc_on_page(len, &(annuary.large));
}

void *malloc(size_t len)
{
	void *ad;

//	putint_endln((unsigned long long)len, 10, "malloc : ", 1);
	lock();
	ad = do_malloc(len);
	unlock();
//	plog("end malloc\n");
	return ad;
}

void	show_alloc_mem()
{
	lock();
	if (!annuary.tiny && !annuary.small && ! annuary.large)
		putstr("NO MEMORY ALLOCATION\n");
	show_alloc_page(annuary.tiny, "TINY");
	show_alloc_page(annuary.small, "SMALL");
	show_alloc_page(annuary.large, "LARGE");
	unlock();
}

void	do_dump_alloc_mem(void *ad)
{
	if (dump_alloc_page(ad, annuary.tiny, "TINY"))
		return ;
	if (dump_alloc_page(ad, annuary.small, "SMALL"))
		return ;
	if (dump_alloc_page(ad, annuary.large, "LARGE"))
		return ;
	putint((unsigned long long)ad, 16, "0x", 1);
	putstr(" : no memory allocation to this adress\n");
}

void	dump_alloc_mem(void *ad)
{
	lock();
	do_dump_alloc_mem(ad);
	unlock();
}

void	free(void *ad)
{
//	putint_endln((unsigned long long)ad, 16, "free : 0x", 1);
	lock();
	do_free(ad);
	unlock();
//	plog("end free\n");
}

void	do_free(void *ad)
{
	free_page(ad, annuary.tiny);
	free_page(ad, annuary.small);
	free_page(ad, annuary.large);
}

void	*do_realloc(void *ad, size_t size)
{
	void *r;

	r = 0;
	if (!ad)
		return do_malloc(size);
	if (size == 0)
	{
		do_free(ad);
		return 0;
	}
	if (!r && (r = realloc_page(ad, size, annuary.tiny)))
		return r;
	if (!r && (r = realloc_page(ad, size, annuary.small)))
		return r;
	if (!r && (r = realloc_page(ad, size, annuary.large)))
		return r;
	return 0;
}

void *realloc(void *ad, size_t len)
{
	void *r;

//	putint_endln((unsigned long long)ad, 16, "realloc : 0x", 1);
	lock();
	r = do_realloc(ad, len);
	unlock();
//	plog("end realloc\n");
	return r;
}
