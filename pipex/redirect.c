#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int set_infile(int fd_in, t_process *p)
{
	int fd;

	if (p->infile != NULL)
	{
		fd = open(p->infile, p->inflag);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
	} else if (!(p->pflag & PF_FIRST)) {
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(fd_in);
	}
	return (1);
}

static int  set_outfile(int pipe[2], t_process *p)
{
	int fd;

	if (p->outfile != NULL)
	{
		fd = open(p->outfile, p->outflag, 0644);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			return (-1);
		}
		close(fd);
	}
	else if (!(p->pflag & PF_LAST))
	{
		if (dup2(pipe[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		close(pipe[READ]);
		close(pipe[WRITE]);
	}
	return (1);
}

int do_redirect(int fd_in, int pipe[2], t_process *p)
{
	if (set_infile(fd_in, p) == -1)
	{
		perror("dup2");
		return (-1);
	}
	if (set_outfile(pipe, p) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (1);
}
