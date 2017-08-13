#include "libft_malloc.h"

#define I 100
#define J 1000

void fill(char *ad, size_t len)
{
	for(size_t i = 0; i < len; i++)
		ad[i] = i;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	size_t len = 100000;
	void *ad[J][I];
	putint_endln((unsigned long long)sizeof(memory_page), 16, "size of page header : ", 1);
	putint_endln((unsigned long long)sizeof(memory_allocation), 16, "size of alloc header : ", 1);
	for (int j =0; j < J; j++)
	{
		putint(j, 10, "alloc ", 1);
		putint_endln(J, 10, "/", 1);
		for(int i = 0; i < I; i++)
		{
			ad[j][i] = malloc(len);
			if (ad[j][i] == 0)
				putstr("error\n");
		}
	}
	show_alloc_mem();
	for (int j =0; j < J; j++)
	{
		putint(j, 10, "fill ", 1);
		putint_endln(J, 10, "/", 1);
		for(int i = 0; i < I; i++)
			fill(ad[i][j], len);
	}
	putstr("/////////////////////////////\n");
	show_alloc_mem();
	for (int j = J-1; j >= 0; j--)
	{
		putint(j, 10, "free ", 1);
		putint_endln(J, 10, "/", 1);
		for(int i = I-1; i >= 0; i--)
			free(ad[j][i]);
	}
	putstr("/////////////////////////////\n");
	show_alloc_mem();
	return 0;
}
