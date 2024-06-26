#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <fcntl.h>


// redirects input and output if needed
// return 1 on success
// return -1 on fail
int     redirect(int pipefd[2], t_process *p)     
{
    int fd;

    // INPUT

    if (p->infile != NULL) // INFILE SET, READ INFILE
    {
        fd = open(p->infile, p->inflag);
        if (fd == -1)
            return (-1);
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            ft_printf("dup2 fail\n");
            close(fd);   
            return (-1);
        }
        //ft_printf_fd(STDERR_FILENO, "read from file %d\n", fd);
        close(fd);
    }
    else if (!(p->pflag & PF_FIRST)) // NOT FIRST CHILD, READ PIPE
    {
        //ft_printf_fd(STDERR_FILENO, "read from pipe cur %d\n", pipefd[READ]);
        if (dup2(pipefd[READ], STDIN_FILENO) == -1) // copy read into stdin
        {
            ft_printf_fd(STDERR_FILENO, "dup2 fail\n");
            return (-1);
        }
        //ft_printf_fd(STDERR_FILENO, "read from pipe after %d\n", pipefd[READ]);
        close(pipefd[READ]); // close read end
    }
    else // FIRST CHILD, CLOSE READ PIPE
        close(pipefd[READ]);




    // OUTPUT

    if (p->outfile != NULL) // OUTFILE SET, WRITE OUTFILE
    {
        fd = open(p->outfile, p->outflag, 0644);
        if (fd == -1)
            return (-1);
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            ft_printf_fd(STDERR_FILENO, "dup2 fail\n");
            close(fd);
            return (-1);
        }
        //ft_printf_fd(STDERR_FILENO, "write to file %d\n", fd);
        close(fd);
    }
    else if (!(p->pflag & PF_LAST)) // NOT LAST, WRITE PIPE
    {
        //ft_printf_fd(STDERR_FILENO, "write to pipe, cur %d, %d\n", pipefd[WRITE], STDOUT_FILENO);
        if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1) // copy write into stdout
        {
            ft_printf_fd(STDERR_FILENO, "dup2 fail\n");
            return (-1);
        }
        //ft_printf_fd(STDERR_FILENO, "write to pipe, after %d, %d\n", pipefd[WRITE], STDOUT_FILENO);
        close(pipefd[WRITE]); // close write end
    }
    else // LAST CHILD, WRITE STDOUT
        close(pipefd[WRITE]);


    return (1);
}
