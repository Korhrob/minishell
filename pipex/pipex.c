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

static int	*init_pid_arr(t_runtime *runtime)
{
	int	*pid_arr;

	pid_arr = malloc(sizeof(int) * runtime->pipe_count);
	if (pid_arr == NULL)
		return (NULL);
	ft_memset(pid_arr, 0, runtime->pipe_count);
	return (pid_arr);
}

static void	exec_process(int fd[2], int *pid_arr, int index, t_process *p)
{
	pid_arr[index] = fork();
	if (pid_arr[index] == -1)
		exit(1);
	if (!pid_arr[index])
	{
		if (redirect(fd, p) == -1)
			exit(1); // could return here instead
		close(fd[0]);
		if (p->pflag & PF_LAST)
			close(fd[1]);
		child(fd, p);
	}
}

static void wait_all_pid(int *pid_arr, t_runtime *runtime)
{
	int	index;
	int	status;

	(void) pid_arr;
	index = 0;
	status = 0;
	while (index < runtime->pipe_count)
	{
		waitpid(pid_arr[index], &status, 0);
		index++;
	}
}

// pipe once and and execute all child processes in forks
void pipex(t_list *list, t_runtime *runtime)
{
	t_list	*cur;
	int fd[2];
	int index;
	int	*pid_arr;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit (1); // could return here instead
	}
	pid_arr = init_pid_arr(runtime);
	if (pid_arr == NULL)
		exit(1);
	index = 0;
	cur = list;
	while (cur != NULL)
	{
		exec_process(fd, pid_arr, index, cur->content);
		index++;
		cur = cur->next;
	}
	close(fd[1]);
	close(fd[0]);
	wait_all_pid(pid_arr, runtime);
	free(pid_arr);
}

