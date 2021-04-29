#include <stdlib.h>

int g_counter_re = 0;

void *malloc_re(size_t size)
{
	g_counter_re++;
	return malloc(size);
}

void free_re(void *ptr)
{
	free(ptr);
	if(ptr != 0)
		g_counter_re--;
}

