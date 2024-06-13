#include "../minishell.h"
#include <unistd.h>
#include <fcntl.h>

static int	redirect_fd(int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		close(input);
		return (-1);
	}
	close (input);
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		close(output);
		return (-1);
	}
	close(output);
	return (1);
}

// redirects input and output if needed
int     redirect(int pipefd[2], t_process *process)
{
    int fd;

    if (process->infile != NULL) // input is set, use input
    {
        fd = open(process->infile, O_RDONLY);
        if (fd == -1)
            return (-1); // open fail
        if (redirect_fd(fd, pipefd[1]) == -1)
            return (-1); // dup2 fail
        close(pipefd[0]);
    }
    // else if ?
    if (process->outfile != NULL) // input is set, use input
    {
        fd = open(process->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return (-1); // open fail
        if (redirect_fd(pipefd[0], fd) == -1)
            return (-1); // dup2 fail
        close(pipefd[0]);
    }
    return (1);
}
