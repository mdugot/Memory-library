#include "libft_malloc.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	size_t len = 1;
	putint_endln((unsigned long long)sizeof(memory_page), 16, "size of page header : ", 1);
	putint_endln((unsigned long long)sizeof(memory_allocation), 16, "size of alloc header : ", 1);
	char *test = malloc(len);
	char *test2 = malloc(len);
	char *test3 = malloc(len);
	char *test4 = malloc(len);
	show_alloc_mem();
	(void)test2;
	(void)test4;
	free(test);
	free(test3);
	show_alloc_mem();
	test = malloc(len);
	show_alloc_mem();
	test3 = malloc(len);
//	dump_alloc_mem(test);
	show_alloc_mem();
	return 0;
}
