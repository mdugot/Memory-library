#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include "libft_malloc.h"

void putstr(char *str) {
	int i = 0;
	while (str[i] != 0)
		i++;
	write(1, str, i);
}

void putint(unsigned long long int n, unsigned int base, char* end) {
	char s[] = "0123456789ABCDEF";
	char tmp;
	unsigned long long int i = 1;
	unsigned long long int m = n;

	if (n == 0)
	{
		write(1, "0", 1);
		putstr(end);
		return;
	}

	while (m >= base) {
		m /= base;
		i *= base;
	}
	while (i > 0) {
		tmp = s[n / i];
		write(1, &tmp, 1);
		n %= i;
		i /= base;
	}
	putstr(end);
}

void print_content(char *memory, size_t len)
{
	size_t i = 0;
	int rows = 16;

	while (i < len) {
		putint((unsigned long long)memory[i], 16, " ");
		i++;
		if (i % rows == 0)
			putstr("\n");
	}
	putstr("\n");
}

void malloc() {
	struct rlimit rl;
	putstr("page size : ");
	putint(getpagesize(), 16, "\n");
	if (getrlimit(RLIMIT_DATA, &rl) == -1)
		putstr("error getrlimit\n");
	putstr("data limit current : ");
	putint(rl.rlim_cur, 16, "\n");
	putstr("data limit max : ");
	putint(rl.rlim_max, 16, "\n");

	size_t len = 64;
	char *ad = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	char *ad2 = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (ad == MAP_FAILED)
		putstr("map failed\n");
	putstr("adress : ");
	putint((long long int)ad, 16, "\n");
	ad[3] = '*';
	ad2[1] = 'a';
	putstr("content : \n");
	print_content(ad, len);
	putstr("adress second map : ");
	putint((long long int)ad2, 16, "\n");
	putstr("content second map: \n");
	print_content(ad2, len);
	if (munmap(ad, len) == -1)
		putstr("munmap error");
	char *ad3 = mmap(0, len, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	ad3[16] = ' ';
	putstr("adress third map after unmap: ");
	putint((long long int)ad3, 16, "\n");
	putstr("content third map after unmap: \n");
	print_content(ad3, len);
}
