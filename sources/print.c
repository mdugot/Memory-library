#include "libft_malloc.h"

void log(char *str)
{
	int i = 0;
	while (str[i] != 0)
		i++;
	write(2, str, i);
}

void putstr(char *str)
{
	int i = 0;
	while (str[i] != 0)
		i++;
	write(1, str, i);
}

void putstr_fd(char *str, int fd)
{
	int i = 0;
	while (str[i] != 0)
		i++;
	write(fd, str, i);
}

static void putintwidth(int width, int fd)
{
	while (width > 0)
	{
		putstr_fd("0", fd);
		width--;
	}
}

void putint_fd(unsigned long long int n, unsigned int base, char* prefix, int width, int fd)
{
	char s[] = "0123456789ABCDEF";
	char tmp;
	unsigned long long int i = 1;
	unsigned long long int m = n;

	putstr_fd(prefix, fd);
	if (n == 0)
	{
		putintwidth(width, fd);
		return;
	}

	width--;
	while (m >= base) {
		m /= base;
		i *= base;
		width--;
	}
	putintwidth(width, fd);
	while (i > 0) {
		tmp = s[n / i];
		write(fd, &tmp, 1);
		n %= i;
		i /= base;
	}
}

void putint(unsigned long long int n, unsigned int base, char* prefix, int width)
{
	putint_fd(n, base, prefix, width, 1);
}

void putint_endln(unsigned long long int n, unsigned int base, char* prefix, int width)
{
	putint_fd(n, base, prefix, width, 1);
	putstr("\n");
}

void logint(unsigned long long int n, unsigned int base, char* prefix, int width)
{
	putint_fd(n, base, prefix, width, 2);
	putstr_fd("\n", 2);
}

void dump_content(unsigned char *memory, size_t len)
{
	size_t i = 0;
	int rows = 16;

//	logint((unsigned long long)memory, 16, "start dump = 0x", 1);
	while (i < len) {
//		logint((unsigned long long)i, 10, "index = ", 1);
//		logint((unsigned long long)len, 10, "len = ", 1);
//		putint((unsigned long long)memory[i], 16, "", 2);
		char debug = memory[i];
		(void)debug;
		putstr(" ");
		i++;
		if (i % rows == 0)
			putstr("\n");
	}
	putstr("\n");
}
