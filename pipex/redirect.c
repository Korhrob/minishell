#include "../minishell.h"
#include <unistd.h>
#include <fcntl.h>

// redirects input and output if needed
// return 1 on success
// return -1 on fail
int     redirect(int pipefd[2], t_process *p)
{
    int fd;

    if (!(p->pflag & PF_FIRST))
    {
        if (dup2(pipefd[0], STDIN_FILENO) == -1)
            return (-1);
        close(pipefd[0]);
    }

    if (!(p->pflag & PF_LAST))
    {
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
            return (-1);
        close(pipefd[1]);
    }

    if (p->infile != NULL)
    {
        fd = open(p->infile, p->inflag);
        if (fd == -1)
            return (-1);
        if (dup2(fd, STDIN_FILENO) == -1)
            return (-1);
        close(fd);
    }

    if (p->outfile != NULL)
    {
        fd = open(p->outfile, p->outflag, 0644);
        if (fd == -1)
            return (-1);
        if (dup2(fd, STDOUT_FILENO) == -1)
            return (-1);
        close(fd);
    }

    return (1);
}
