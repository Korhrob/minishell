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
	if (redirect(pipefd, process) != 1)
		exit(0);
	if (process->path == NULL)
	{
		ft_printf("no such command %s\n", process->args[0]);
		exit(1);
	}
	if (execve(process->path, process->args, NULL) == -1)
	{
		ft_printf("execve failed\n");
		exit(1);
	}
	exit(0);
}

// begins piping process
void	begin_pipe(t_process *process)
{
	int		pipefd[2];
	int		cid;
	int		status;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ; //pipe failed
	}
	cid = fork();
	if (cid == -1)
	{
		perror("fork");
		return ; // fork failed
	}
	if (cid == 0)
	{
		close(pipefd[0]);
		child(pipefd, process);
	}
	else
		close(pipefd[1]);
	if (!(process->pflag & PF_LAST))
		close(pipefd[1]);
	status = 0;
	waitpid(cid, &status, 0);
}
