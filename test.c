#include "libft_malloc.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#define NTHREAD 10
#define MIN_SIZE 1
#define MAX_SIZE 1000000
#define MAX_FAIL 10000000000000000
//#define N 1000000
#define N 100000
#define LOOP 1000

static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
static int printing = 0;

void plock()
{
	pthread_mutex_lock(&print_mutex);
	printing = 1;
}

void punlock()
{
	printing = 0;
	pthread_mutex_unlock(&print_mutex);
}

void fill(unsigned char *ad, size_t len, unsigned char c)
{
	if (!ad)
		return;
	for(size_t i = 0; i < len; i++)
		ad[i] = c;
}

size_t nrandom(size_t min, size_t max)
{
	return rand() % (max-min) + min;
}

size_t rsize()
{
	int min, max;
	int r = nrandom(0, 5);
	if (r == 0)
		return 0;
	else if (r == 1) {
		min = MIN_SIZE;
		max = TINY_ALLOCATION;
	} else if (r == 2) {
		min = TINY_ALLOCATION;
		max = SMALL_ALLOCATION;
	} else if (r == 3) {
		min = SMALL_ALLOCATION;
		max = MAX_SIZE;
	} else
		return MAX_FAIL;
	return nrandom(min, max);
}

void free_memory(unsigned char *mem[])
{
	int n = nrandom(0, N);
	dprintf(2, "free : %p\n", mem[n]);
	free(mem[n]);
	mem[n] = 0;
}

void alloc_memory(unsigned char *mem[])
{
	int n = nrandom(0, N);
	size_t len = rsize();
	dprintf(2, "alloc show : %zu -> %p\n", len, mem[n]);
	if (mem[n])
		mem[n] = realloc(mem[n], len);
	else
		mem[n] = malloc(len);
//	unsigned char c = nrandom(0, 256);
//	fill(mem[n], len, c);
}

void show_memory(unsigned char *mem[])
{
	int n = nrandom(0, N);
	dprintf(2, "show : %p\n", mem[n]);
	dump_alloc_mem(mem[n]);
}

void *process_memory(void *arg)
{
	unsigned char **mem = arg;
	while (1)
	{
		for (int i = 0; i < LOOP; i++)
		{
			int r = nrandom(0, 4);
			if (r == 0)
				free_memory(mem);
			else if (r == 1)
				alloc_memory(mem);
			else if (r == 2)
				show_memory(mem);
			else
				show_alloc_mem();
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char *mem[N] = {0};
	srand(time(0));
	pthread_t thread_id[NTHREAD];
	for (int i = 0; i < NTHREAD; i++)
	{
		if (pthread_create(&thread_id[i], 0, process_memory, mem))
		{
			dprintf(2, "error\n");
			return 1;
		}
	}
	process_memory(mem);
	return 0;
}
