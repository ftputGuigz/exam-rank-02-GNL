#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int i;
	char *line;

	line = NULL;
	while ((i = get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	line = NULL;
}

