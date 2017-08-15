#ifndef MEMORY_ANNUARY_H
# define MEMORY_ANNUARY_H

# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

# define TINY_ALLOCATION 1000
# define SMALL_ALLOCATION 10000
# define TINY_PAGE 10
# define SMALL_PAGE 100

typedef struct			memory_allocation
{
	void*						content;
	size_t						len;
	struct memory_allocation 	*next;
}						memory_allocation;

typedef struct			memory_page
{
	void*						adress;
	size_t						size;
	size_t						empty_space;
	struct memory_page 			*next;
	struct memory_page 			**origin;
	struct memory_allocation	*content;
}						memory_page;

typedef struct			memory_annuary
{
	size_t						page_size;
	struct memory_page			*tiny;
	struct memory_page			*small;
	struct memory_page			*large;
	struct memory_page			*last_tiny;
	struct memory_page			*last_small;
	struct memory_page			*last_large;
}						memory_annuary;


memory_annuary	*get_annuary();
void clean_memory(char* ad, size_t len);
void copy_memory(char* ad, char *mem, size_t len);
size_t	get_page_size(size_t len);
void *get_end_page(memory_page *p);
void *get_end(memory_allocation *m);
size_t get_first_size(size_t len);
size_t get_size(size_t len);
memory_allocation	*create_allocation(memory_page *page, size_t len);
memory_page	*new_memory_page(memory_page *last, size_t size, size_t len, memory_page **origin);
void putint(unsigned long long int n, unsigned int base, char* prefix, int width);
void putint_endln(unsigned long long int n, unsigned int base, char* prefix, int width);
void putstr(char *str);
void	show_alloc_page(memory_page* page, char *type);
void dump_content(unsigned char *memory, size_t len);
int	dump_alloc_page(void *ad, memory_page* page, char *type);
void alloc_info();
int	free_page(void* ad, memory_page *page);
int is_in(memory_page* page, void *ad);
void clean_page(memory_page *page);
void set_last_page(size_t len, memory_page *page);
memory_page	*get_last_page(size_t len);
memory_allocation *find_in_page(void *ad, memory_page *begin, memory_allocation **alast, memory_page **apage);
void delete_allocation(memory_page *page, memory_allocation *mem, memory_allocation *last);
void *realloc_page(void *ad, size_t len, memory_page *begin);
int	same_type(size_t lena, size_t lenb);

#endif
