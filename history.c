#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include <readline/history.h>

static int	history_line_count(void)
{
	int		count;
	int		fd;
	char	buf;

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

	add_history(line);
	fd = open(".history", O_WRONLY | O_CREAT | O_APPEND, 
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return ;
	count = history_line_count();
	ft_putstr_fd("  ", fd);
	ft_putstr_fd(ft_itoa(count), fd);
	ft_putstr_fd("  ", fd);
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}

// print all history starting from the beginning
void	print_history_all(void)
{
	int		fd;
	char	*line;

	fd = open(".history", O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_printf("%s", line);
		line = get_next_line(fd);
	}
	close(fd);
}

// reads all history and saves lines to list
// requires fd where to read from
// mode 0 = standard
// mode 1 = reversed
t_list	**read_to_list(int fd, int mode)
{
	t_list	**list;
	t_list	*ele;
	char	*line;

	list = ft_lst_create();
	if (list == NULL)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ele = ft_lstnew(line);
		if (ele == NULL)
			break ;
		if (mode == 0)
			ft_lstadd_back(list, ele);
		else
			ft_lstadd_front(list, ele);
		line = get_next_line(fd);
	}
	return (list);
}

// print n number of most recent history
void	print_history_n(int n)
{
	int		fd;
	int		skip;
	t_list	**list;
	t_list	*cur;

	fd = open(".history", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("error: no history");
		return ;
	}
	list = read_to_list(fd, 0);
	close(fd);
	if (list == NULL)
		return ;
	cur = *list;
	skip = ft_lstsize(*list) - n;
	while (skip-- > 0 && cur->next != NULL)
		cur = cur->next;
	while (n-- > 0 && cur != NULL)
	{
		ft_printf("%s", cur->content);
		cur = cur->next;
	}
	ft_lst_clean(list, 1);
}

void	print_history(char **next_arg)
{
	int		count;

	count = -1;
	if (*next_arg != NULL)
	{
		if (ft_isdigit_str(*next_arg))
			count = ft_atoi(*next_arg);
		else
		{
			ft_printf("numeric argument required\n");
			return ;
		}
	}
	if (count == -1)
		print_history_all();
	else
		print_history_n(count);
}
