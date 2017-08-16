#include "libft_malloc.h"

static memory_annuary annuary = {0, 0, 0, 0, 0, 0, 0};
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void alloc_info()
{
	struct rlimit rl;
	size_t ps = getpagesize();
	putstr("\n------------\n");
	putstr("page size : ");
	putint_endln(ps, 10, "", 1);
	if (getrlimit(RLIMIT_DATA, &rl) == -1)
		putstr("error getrlimit\n");
	putstr("data limit current : ");
	putint_endln(rl.rlim_cur, 16, "", 1);
	putstr("data limit max : ");
	putint_endln(rl.rlim_max, 16, "", 1);
	if (getrlimit(RLIMIT_MEMLOCK, &rl) == -1)
		putstr("error getrlimit\n");
	putstr("melock limit current : ");
	putint_endln(rl.rlim_cur, 16, "", 1);
	putstr("memlock limit max : ");
	putint_endln(rl.rlim_max, 16, "", 1);
	if (getrlimit(RLIMIT_RSS, &rl) == -1)
		putstr("error getrlimit\n");
	putstr("rss limit current : ");
	putint_endln(rl.rlim_cur, 16, "", 1);
	putstr("rss limit max : ");
	putint_endln(rl.rlim_max, 16, "", 1);

	putstr("------------\n\n");
}

void test() {

	alloc_info();

	size_t len = 32;
	unsigned char *ad = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	unsigned char *ad2 = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (ad == MAP_FAILED)
		putstr("map failed\n");
	putstr("adress : ");
	putint_endln((long long int)ad, 16, "", 1);
	ad[3] = '*';
	ad2[1] = 'a';
	putstr("content : \n");
	dump_content(ad, len);
	putstr("adress second map : ");
	putint_endln((long long int)ad2, 16, "", 1);
	putstr("content second map: \n");
	dump_content(ad2, len);
	if (munmap(ad, len) == -1)
		putstr("munmap error");
	unsigned char *ad3 = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	ad3[16] = ' ';
	putstr("adress third map after unmap: ");
	putint_endln((long long int)ad3, 16, "", 1);
	putstr("content third map after unmap: \n");
	dump_content(ad3, len);

	alloc_info();
}

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
		return (tmp_page->content->content);
	}
	tmp_mem = create_allocation(*page, len);
	if (!tmp_mem)
		return 0;
	return tmp_mem->content;
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

	lock();
	ad = do_malloc(len);
	unlock();
	return ad;
}

void	show_alloc_mem()
{
	if (!annuary.tiny && !annuary.small && ! annuary.large)
		putstr("NO MEMORY ALLOCATION\n");
	show_alloc_page(annuary.tiny, "TINY");
	show_alloc_page(annuary.small, "SMALL");
	show_alloc_page(annuary.large, "LARGE");
}

void	dump_alloc_mem(void *ad)
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

void	free(void *ad)
{
	lock();
	do_free(ad);
	unlock();
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
	return do_malloc(size);
}

void *realloc(void *ad, size_t len)
{
	void *r;

	lock();
	r = do_realloc(ad, len);
	unlock();
	return r;
}
