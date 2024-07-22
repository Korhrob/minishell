/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <readline/history.h>

void	record_history(char *line, t_runtime *runtime)
{
	int		fd;
	int		count;
	char	*i;

	add_history(line);
	if (runtime->history == NULL)
		return ;
	fd = open(runtime->history, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		return ;
	count = runtime->history_line_count++;
	i = ft_itoa(1 + count);
	ft_putstr_fd("  ", fd);
	ft_putstr_fd(i, fd);
	ft_putstr_fd("  ", fd);
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	free(i);
}

// print all history starting from the beginning
static int	print_history_all(t_runtime *runtime, int fd_out)
{
	int		fd;
	char	*line;

	fd = open(runtime->history, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "history: no history file\n");
		return (EXIT_SUCCESS);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_printf_fd(fd_out, "%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

// reads all history and saves lines to list and close the fd
// requires fd where to read from
// mode 0 = ascending
// mode 1 = descending (reverse)
static t_list	*read_to_list(int fd, int mode)
{
	t_list	*list;
	t_list	*ele;
	char	*line;

	list = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ele = ft_lstnew(line);
		if (ele == NULL)
			break ;
		if (mode == 0)
			ft_lstadd_back(&list, ele);
		else
			ft_lstadd_front(&list, ele);
		line = get_next_line(fd);
	}
	close(fd);
	return (list);
}

// print n number of most recent history
static int	print_history_n(int n, t_runtime *runtime, int fd_out)
{
	int		fd;
	int		skip;
	t_list	*list;
	t_list	*cur;

	fd = open(runtime->history, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "history: no history file\n");
		return (EXIT_FAILURE);
	}
	list = read_to_list(fd, 0);
	if (list == NULL)
		return (MALLOC_FAIL);
	cur = list;
	skip = ft_lstsize(list) - n;
	while (skip-- > 0 && cur->next != NULL)
		cur = cur->next;
	while (n-- > 0 && cur != NULL)
	{
		ft_printf_fd(fd_out, "%s", cur->content);
		cur = cur->next;
	}
	ft_lst_clean(&list);
	return (EXIT_SUCCESS);
}

// print history, if next arg is set to integer
// print only most recently history until n
int	print_history(char **next_arg, t_runtime *runtime, int fd)
{
	int		count;
	int		ret;

	count = -1;
	if (*next_arg != NULL)
	{
		if (ft_isdigit_str(*next_arg))
			count = ft_atoi(*next_arg);
		else
		{
			ft_printf_fd(STDERR_FILENO, "history: numeric argument required\n");
			return (EXIT_FAILURE);
		}
	}
	if (runtime->history == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "history: null history file\n");
		return (EXIT_FAILURE);
	}
	if (count == -1)
		ret = print_history_all(runtime, fd);
	else
		ret = print_history_n(count, runtime, fd);
	return (ret);
}
