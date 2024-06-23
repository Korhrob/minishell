#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// NOTE: move to libft
int	file_line_count(char *file)
{
	int		count;
	int		fd;
	char	buf;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
			count++;
	}
	close(fd);
	return (count);
}