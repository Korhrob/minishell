#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int  set_input(int pipefd[2], t_process *p)
{
    int fd;

    if (p->infile != NULL) // INFILE SET, READ INFILE
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
    }
    else if (!(p->pflag & PF_FIRST)) // NOT FIRST CHILD, READ PIPE
    {
        if (dup2(pipefd[READ], STDIN_FILENO) == -1) // copy read into stdin
            return (-1);
        close(pipefd[READ]); // close read end
    }
    else // FIRST CHILD, CLOSE READ PIPE
        close(pipefd[READ]);
    return (1);
}

static int  set_output(int pipefd[2], t_process *p)
{
    int fd;

    if (p->outfile != NULL) // OUTFILE SET, WRITE OUTFILE
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
    else if (!(p->pflag & PF_LAST)) // NOT LAST, WRITE PIPE
    {
        if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1) // copy write into stdout
            return (-1);
        close(pipefd[WRITE]); // close write end
    }
    else // LAST CHILD, WRITE STDOUT
        close(pipefd[WRITE]);
    return (1);
}

// redirects input and output if needed
// return 1 on success
// return -1 on fail
int     redirect(int pipefd[2], t_process *p)     
{
    if (set_input(pipefd, p) == -1)
    {
        perror("dup2");
        return (-1);
    }
    if (set_output(pipefd, p) == -1)
    {
        perror("dup2");
        return (-1);
    }
    return (1);
}

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
    /*
    if (!(p->pflag & PF_FIRST))
    {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    */
    if (set_infile(fd_in, p) == -1)
    {
        //dup error
        return (-1);
    }
    if (set_outfile(pipe, p) == -1)
    {
        //dup error
        return (-1);
    }
    /*
    if (!(p->pflag & PF_LAST))
    {
        dup2(pipe[WRITE], STDOUT_FILENO);
        close(pipe[READ]);
        close(pipe[WRITE]);
    }
    */
    return (1);
}