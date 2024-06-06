#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libft/libft.h"

static int history_line_count()
{
	int	count;
	int	fd;
	char buf;

	count = 0;
	fd = open(".history", O_RDONLY);
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

void	record_history(char *line)
{
	int	fd;
	int	count;

	fd = open(".history", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		ft_printf("error: no perms\n");
		return ;
	}
	ft_putchar_fd('\t', fd);
	count = history_line_count();
	ft_putstr_fd(ft_itoa(count), fd);
	ft_putchar_fd('\t', fd);
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}