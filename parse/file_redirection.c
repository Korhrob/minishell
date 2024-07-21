/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int	in_heredoc(t_process *p, t_runtime *runtime)
{
	if (p->infile != NULL)
		free(p->infile);
	p->infile = ft_strdup(runtime->heredoc);
	if (p->infile == NULL && !(p->eflag & MALLOC_FAIL))
		p->eflag |= MALLOC_FAIL;
	p->inflag = O_RDONLY;
	p->fflag = 1;
	return (2);
}

static int	in_file(t_process *p, char *line)
{
	char	*filename;
	int		fd;

	if (p->infile != NULL)
		free(p->infile);
	p->inflag = O_RDONLY;
	filename = get_filename(line);
	fd = open(filename, p->inflag);
	if (fd == -1)
	{
		free(filename);
		p->eflag = FILE_FAIL;
		return (1);
	}
	p->infile = filename;
	if (p->infile == NULL && !(p->eflag & MALLOC_FAIL))
		p->eflag |= MALLOC_FAIL;
	p->fflag = 0;
	close(fd);
	return (1);
}

static int	out_file_append(t_process *p, char *line)
{
	char	*filename;
	int		fd;

	if (p->outfile != NULL)
		free(p->outfile);
	p->outflag = O_WRONLY | O_CREAT | O_APPEND;
	filename = get_filename(line);
	fd = open(filename, p->outflag, 0777);
	if (fd == -1)
	{
		free(filename);
		p->eflag |= FILE_FAIL;
		return (2);
	}
	p->outfile = filename;
	if (p->outfile == NULL && !(p->eflag & MALLOC_FAIL))
		p->eflag |= MALLOC_FAIL;
	close(fd);
	return (2);
}

static int	out_file(t_process *p, char *line)
{
	char	*filename;
	int		fd;

	if (p->outfile != NULL)
		free(p->outfile);
	p->outflag = O_WRONLY | O_CREAT | O_TRUNC;
	filename = get_filename(line);
	fd = open(filename, p->outflag, 0777);
	if (fd == -1)
	{
		free(filename);
		p->eflag |= FILE_FAIL;
		return (1);
	}
	p->outfile = filename;
	if (p->outfile == NULL && !(p->eflag & MALLOC_FAIL))
		p->eflag |= MALLOC_FAIL;
	close (fd);
	return (1);
}

// initialize redirections, heredoc and file flags
void	file_redirection(t_process *p, t_runtime *runtime)
{
	char	*ptr;

	ptr = p->line;
	p->fflag = 0;
	while (*ptr != 0)
	{
		if (*ptr == '\'' || *ptr == '\"')
			ptr += ft_strlen_t(ptr, *ptr);
		else if (ft_strncmp(ptr, "<<", 2) == 0)
			ptr += in_heredoc(p, runtime);
		else if (ft_strncmp(ptr, ">>", 2) == 0)
			ptr += out_file_append(p, ptr + 2);
		else if (ft_strncmp(ptr, "<", 1) == 0)
			ptr += in_file(p, ptr + 1);
		else if (ft_strncmp(ptr, ">", 1) == 0)
			ptr += out_file(p, ptr + 1);
		else
			ptr++;
		if (p->eflag != 0)
			break ;
	}
}
