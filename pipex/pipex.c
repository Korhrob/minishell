#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <elf.h>
#include <fcntl.h>

static int	is_executable(char *file)
{
	int				fd;
	unsigned char	e_ident[EI_NIDENT];

	if (access(file, X_OK) == 0)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	if (read(fd, e_ident, EI_NIDENT) != EI_NIDENT) {
		perror("read");
		close(fd);
		return 0;
	}
	close(fd);
	if (e_ident[EI_MAG0] == ELFMAG0 &&
		e_ident[EI_MAG1] == ELFMAG1 &&
		e_ident[EI_MAG2] == ELFMAG2 &&
		e_ident[EI_MAG3] == ELFMAG3)
	{
		return (1);  // It's an ELF file
	}
	return (0);
}

static void	child(t_process *process)
{
	if (process->path == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "no such command %s\n", process->args[0]);
		exit(1);
	}
	if (!is_executable(process->path))
	{
		//ft_printf_fd(STDERR_FILENO, "not executable\n");
	}
	if (execve(process->path, process->args, NULL) == -1)
	{
		perror("execve");
		//ft_printf_fd(STDERR_FILENO, "execve failed\n");
		exit(1);
	}
	ft_printf_fd(STDERR_FILENO, "execve failed\n");
	exit(1);
}

static void end_pipe(int fd[2], t_pipe *pipe_info, t_process *p)
{
	if (!(p->pflag & PF_FIRST))
		close(pipe_info->fd_in);
	if (!(p->pflag & PF_LAST))
	{
		close(fd[WRITE]);
		pipe_info->fd_out = fd[READ];
	}
}

static void do_pipe(t_pipe *pipe_info, t_process *p)
{
	int	fd[2];
	int	pid;

	if (!(p->pflag & PF_LAST) && pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	if ((pid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		if (do_redirect(pipe_info->fd_in, fd, p) == -1)
			exit(1);
		child(p);
	}
	end_pipe(fd, pipe_info, p);
}

// pipe once and and execute all child processes in forks
void pipex(t_list *list)
{
	t_pipe	pipe_info;
	int		pid;
	int		status;

	pipe_info.fd_in = -1;
	pipe_info.fd_out = -1;
	while (list != NULL)
	{
		do_pipe(&pipe_info, list->content);
		list = list->next;
		if (pipe_info.fd_out != -1)
			pipe_info.fd_in = pipe_info.fd_out;
	}
	pid = wait(&status);
	while (pid > 0)
		pid = wait(&status);
	// perror("wait");
}

