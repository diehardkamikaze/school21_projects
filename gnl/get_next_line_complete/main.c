#include <fcntl.h>
#include <printf.h>
#include "get_next_line.h"

int main()
{
	char *line = 0;
	int i = 0;
	int fd = 0;

	fd= open(0, O_RDONLY);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("%d : %s\n", i, line);
		free(line);
	}
	printf("%d : %s\n", i, line);
	free(line);
	i = get_next_line(fd, &line);
	printf("%d : %s\n", i, line);
	free(line);

	}
