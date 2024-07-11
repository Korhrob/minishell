#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <elf.h>
#include <fcntl.h>

static void	child(t_process *process, t_runtime *runtime)
{
	int builtin; 

	if (process->args[0] == NULL)
		exit(1);
	builtin = get_builtin(process->args[0]);
	if (builtin != -1)
	{
		do_builtin(process, builtin, runtime, STDOUT_FILENO);
		exit (EXIT_SUCCESS);
	}
	if (process->path == NULL || access(process->path, F_OK))
	{
		ft_printf_fd(STDERR_FILENO, "idleshell: %s: file not found\n", process->args[0]);
		exit(127);
	}
	if (execve(process->path, process->args, NULL) == -1)
	{
		perror("execve");
		//ft_printf_fd(STDERR_FILENO, "execve failed\n");
		exit(1);
	}
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

static void do_pipe(t_pipe *pipe_info, t_process *p, t_runtime *runtime)
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
	child_signals(pid);
	if (pid == 0)
	{
		if (do_redirect(pipe_info->fd_in, fd, p) == -1)
			exit(1);
		child(p, runtime);
	}
	end_pipe(fd, pipe_info, p);
}

// pipe once and and execute all child processes in forks
void pipex(t_list *list, t_runtime *runtime)
{
	t_pipe	pipe_info;
	int		pid;

	pipe_info.fd_in = -1;
	pipe_info.fd_out = -1;
	while (list != NULL)
	{
		do_pipe(&pipe_info, list->content, runtime);
		list = list->next;
		if (pipe_info.fd_out != -1)
			pipe_info.fd_in = pipe_info.fd_out;
	}
	pid = wait(&runtime->exit_status);
	while (pid > 0)
		pid = wait(&runtime->exit_status);
	// perror("wait");
}

