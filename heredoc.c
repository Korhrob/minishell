/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

static int	set_heredoc_id(t_process *p, t_runtime *runtime)
{
	char	*temp;
	char	*id;

	id = ft_itoa(runtime->pipe_index);
	if (!id)
		return (0);
	temp = ft_strjoin_c(p->infile, id, '_');
	if (!temp)
	{
		free(id);
		return (0);
	}
	free(p->infile);
	free(id);
	p->infile = temp;
	return (1);
}

// process all heredocs but only retain the last one
// return 1 if all heredocs succeed
// return 0 if any heredoc fails
int	process_heredoc(char *line, t_process *p, t_runtime *runtime)
{
	char	*delimiter;

	if (p->fflag != 1)
		return (0);
	if (!set_heredoc_id(p, runtime))
		return (0);
	while (*line != 0)
	{
		if (*line == '\'' || *line == '\"')
			line += ft_strlen_t(line, *line);
		if (ft_strncmp(line, "<<", 2) == 0)
		{
			line += 2;
			delimiter = get_filename(line);
			if (delimiter == NULL)
				return (0);
			ft_heredoc(delimiter, p);
			free(delimiter);
		}
		else
			line++;
		if (g_exit_status)
			break ;
	}
	return (1);
}

// handle heredoc behavior
// only the last heredoc should matter
// and this function shouldnt have to return anything
void	ft_heredoc(char *delimit, t_process *p)
{
	int		fd;
	char	*buffer;

	fd = open(p->infile, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
		return ;
	heredoc_signals();
	while (!g_exit_status)
	{
		buffer = readline("heredoc> ");
		if (buffer == NULL)
			break ;
		if (*buffer == 0)
			continue ;
		if (ft_strcmp(buffer, delimit) == 0)
		{
			free(buffer);
			break ;
		}
		ft_printf_fd(fd, "%s\n", buffer);
		free(buffer);
	}
	close (fd);
}
