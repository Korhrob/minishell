#include "minishell.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <readline/history.h>

// NOTE: move to libft
static int	file_line_count(char *file)
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

// saves in current pwd
// NOTE: does not save heredoc stuff
void	record_history(char *line, t_runtime *runtime)
{
	int		fd;
	int		count;
	char	*i;

	add_history(line);
	fd = open(runtime->history, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return ;
	count = file_line_count(runtime->history);
	i = ft_itoa(count);
	ft_putstr_fd("  ", fd);
	ft_putstr_fd(i, fd);
	ft_putstr_fd("  ", fd);
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	free(i);
}

// print all history starting from the beginning
void	print_history_all(t_runtime *runtime)
{
	int		fd;
	char	*line;

	fd = open(runtime->history, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

// reads all history and saves lines to list
// requires fd where to read from
// mode 0 = ascending
// mode 1 = descending (reverse)
// NOTE: move to libft
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
void	print_history_n(int n, t_runtime *runtime)
{
	int		fd;
	int		skip;
	t_list	**list;
	t_list	*cur;

	fd = open(runtime->history, O_RDONLY);
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

void	print_history(char **next_arg, t_runtime *runtime)
{
	int		count;

	count = -1;
	if (*next_arg != NULL)
	{
		if (ft_isdigit_str(*next_arg))
			count = ft_atoi(*next_arg);
		else
		{
			ft_printf("history: numeric argument required\n");
			return ;
		}
	}
	if (count == -1)
		print_history_all(runtime);
	else
		print_history_n(count, runtime);
}
