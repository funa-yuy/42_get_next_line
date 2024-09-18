
#include <stdio.h>
#include "get_next_line.h"

// int	main()
int	main(int argc, char *argv[])
{
	int		fd;
	char	*one_line;
	// (void)	argc;
	// (void)	argv;

	if (argc <= 1){
		printf("Give file name to process");
		return(1);
	}
	printf("%s\n", argv[1]);
	fd = open(argv[1], O_RDONLY);
	// fd = 5000;
	// fd = open("./char1.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	while ((one_line = get_next_line(fd)) != NULL)
	{
		printf("%s", one_line);
		fflush(stdout);
		free(one_line);
	}
	// printf("close");
	close(fd);
	return (0);
}
