#include "libft_malloc.h"

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *test = malloc(2);
	char *test2 = malloc(10);
	char *test3 = malloc(33);
	malloc(10000);
	malloc(999000);
	for (int i = 0; i < 1000; i++)
	{
		malloc(1000);
	}
	test[0] = 'O';
	test[1] = 'K';
	copy_memory(test3, "this is a test\n", 15);
	show_alloc_mem();
	dump_alloc_mem(test);
	dump_alloc_mem(test + 1);
	dump_alloc_mem(test + 2);
	dump_alloc_mem(test - 1);
	dump_alloc_mem(test2);
	dump_alloc_mem(test3);
	dump_alloc_mem(argv);
	return 0;
}
