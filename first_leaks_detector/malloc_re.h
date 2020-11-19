#include <stdlib.h>

#ifndef MALLOC_RE_H
#define MALLOC_RE_H

int g_counter_re;
void	*malloc_re(size_t size);
void	free_re(void *ptr);

#define malloc(x) malloc_re(x)
#define free(x) free_re(x);

#endif
