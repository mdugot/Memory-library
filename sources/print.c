#include "libft_malloc.h"

void putstr(char *str)
{
	int i = 0;
	while (str[i] != 0)
		i++;
	write(1, str, i);
}

static void putintwidth(int width)
{
	while (width > 0)
	{
		putstr("0");
		width--;
	}
}

void putint(unsigned long long int n, unsigned int base, char* prefix, int width)
{
	char s[] = "0123456789ABCDEF";
	char tmp;
	unsigned long long int i = 1;
	unsigned long long int m = n;

	putstr(prefix);
	if (n == 0)
	{
		putintwidth(width);
		return;
	}

	width--;
	while (m >= base) {
		m /= base;
		i *= base;
		width--;
	}
	putintwidth(width);
	while (i > 0) {
		tmp = s[n / i];
		write(1, &tmp, 1);
		n %= i;
		i /= base;
	}
}

void putint_endln(unsigned long long int n, unsigned int base, char* prefix, int width)
{
	putint(n, base, prefix, width);
	putstr("\n");
}

void dump_content(unsigned char *memory, size_t len)
{
	size_t i = 0;
	int rows = 16;

	while (i < len) {
		putint((unsigned long long)memory[i], 16, "", 2);
		putstr(" ");
		i++;
		if (i % rows == 0)
			putstr("\n");
	}
	putstr("\n");
}
