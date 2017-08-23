#include "libft_malloc.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#define NTHREAD 20
#define MIN_SIZE 1
#define MAX_SIZE 50000
#define MAX_FAIL 10000000000000000
//#define N 1000000
#define N 10000
#define LOOP 1000

//static pthread_mutex_t use_mutex = PTHREAD_MUTEX_INITIALIZER;
static void* inuse = 0;

void ulock(void *ad)
{
	//pthread_mutex_lock(&use_mutex);
	inuse = ad;
	lock();
}

void unulock()
{
	unlock();
	inuse = 0;
	//pthread_mutex_unlock(&use_mutex);
}

void fill(unsigned char *ad, size_t len, unsigned char c)
{
	if (!ad)
		return;
	ulock(ad);
	if (!inuse)
		return;
	for(size_t i = 0; i < len; i++)
		ad[i] = c;
	unulock();
}

size_t nrandom(size_t min, size_t max)
{
	size_t mod = max - min;
	if (mod <= 0)
		return min;
	return rand() % (max-min) + min;
}

size_t rsize()
{
	size_t min, max;
	int r = nrandom(0, 5);
//	int r = 3;
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
	} else {
		min = MAX_FAIL;
		max = MAX_FAIL;
	}
	return nrandom(min, max);
}

void free_memory(unsigned char *mem[])
{
	dprintf(2, "free : begin\n");
	int n = nrandom(0, N);
	dprintf(2, "free : %p\n", mem[n]);
	void *tmp = mem[n];
	if (inuse == mem[n])
		return;
	free(mem[n]);
	mem[n] = 0;
	dprintf(2, "free : end\n");
	if (inuse == tmp)
		inuse = 0;
}

void list_memory()
{
	dprintf(2, "list : begin\n");
	show_alloc_mem();
	dprintf(2, "list : end\n");
}

void random_realloc(unsigned char *mem[])
{
	dprintf(2, "realloc : begin\n");
	int n = nrandom(0, N);
	size_t len = rsize();
	dprintf(2, "realloc : %zu -> %p\n", len, mem[n]);
	void *tmp = mem[n];
	if (inuse == mem[n])
		return;
	mem[n] = realloc(mem[n], len);
	dprintf(2, "realloc : end\n");
	if (inuse == tmp)
		inuse = 0;
}

void alloc_memory(unsigned char *mem[])
{
	dprintf(2, "alloc : begin\n");
	int n = nrandom(0, N);
	size_t len = rsize();
	dprintf(2, "alloc : %zu -> %p\n", len, mem[n]);
	if (mem[n])
		mem[n] = realloc(mem[n], len);
	else
		mem[n] = malloc(len);
//	unsigned char c = nrandom(0, 256);
//	fill(mem[n], len, c);
	dprintf(2, "alloc : end\n");
}

void show_memory(unsigned char *mem[])
{
	dprintf(2, "show : begin\n");
	int n = nrandom(0, N);
	dprintf(2, "show : %p\n", mem[n]);
	dump_alloc_mem(mem[n]);
	dprintf(2, "end show\n");
}

void *process_memory(void *arg)
{
	unsigned char **mem = arg;
	while (1)
	{
		for (int i = 0; i < LOOP; i++)
		{
			int r = nrandom(0, 5);
			if (r == 0)
				free_memory(mem);
			else if (r == 1)
				alloc_memory(mem);
			else if (r == 2)
				show_memory(mem);
			else if (r == 3)
				random_realloc(mem);
			else
				list_memory();
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
