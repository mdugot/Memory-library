#include "libft_malloc.h"

#define L 200

void fill(char *ad, size_t len)
{
	for(size_t i = 0; i < len; i++)
		ad[i] = i;
	dump_alloc_mem(ad);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *ad;
	for (int i = 0; i < 300 ; i++)
		ad = malloc(SMALL_ALLOCATION + 1);
	putint_endln((unsigned long long)get_number_page(get_annuary()->tiny, 0), 10, "number tiny pages : ", 1);
	putint_endln((unsigned long long)get_number_page(get_annuary()->small, 0), 10, "number small pages : ", 1);
	putint_endln((unsigned long long)get_number_page(get_annuary()->large, 0), 10, "number large pages : ", 1);
	return 0;
}

