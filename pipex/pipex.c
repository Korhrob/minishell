#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

//static int validate input / validate output

// child process

static void	child(int pipefd[2], t_process *process)
{
	(void)pipefd;
	if (process->path == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "no such command %s\n", process->args[0]);
		exit(1);
	}
	//ft_printf_fd(STDERR_FILENO, "execve %s %s %s\n", process->path, process->args[0], process->args[1]);
	if (execve(process->path, process->args, NULL) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "execve failed\n");
		exit(1);
	}
	ft_printf_fd(STDERR_FILENO, "execve failed\n");
	exit(1);
}

// pipe once and and execute all child processes in forks
void alt_pipex(t_list *list)
{
	t_process *p;
	int fd[2];
	int pid;

	pipe(fd);
	while (list != NULL)
	{
		p = list->content;
		pid = fork();
		if (!pid)
		{
			if (redirect(fd, p) == -1)
				exit(1); // could return here
			close(fd[0]);
			child(fd, p);
		}
		else
		{
			if (p->pflag & PF_LAST)
				close(fd[1]);
		}
		list = list->next;
	}
	close(fd[1]);
	close(fd[0]);
	wait(NULL); // wait all pids
}

