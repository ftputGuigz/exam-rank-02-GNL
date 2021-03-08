#include "get_next_line.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	int fd; 
	int i;
	char *line;
	(void )ac;

	line = NULL;
	fd = open(av[1], O_RDONLY);
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("line = %s\n", line);
		free(line);
		line = NULL;
	}
	close(fd);
	printf("line = %s\n", line);
	free(line);
	line = NULL;
}
