/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

static void	child(t_process *p, t_runtime *runtime, int builtin_id)
{
	if (builtin_id)
	{
		do_builtin(p, builtin_id, runtime, STDOUT_FILENO);
		exit (EXIT_SUCCESS);
	}
	file_checks(p);
	runtime->envp = convert_environ(runtime->env_struct);
	if (runtime->envp == NULL)
		exit(EXIT_FAILURE);
	if (execve(p->path, p->args, runtime->envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

static void	end_pipe(int fd[2], t_pipe *pipe_info, t_process *p)
{
	if (!(p->pflag & PF_FIRST))
		close(pipe_info->fd_in);
	if (!(p->pflag & PF_LAST))
	{
		close(fd[WRITE]);
		pipe_info->fd_out = fd[READ];
	}
}

static void	do_pipe(t_pipe *pipe_info, t_process *p, t_runtime *runtime)
{
	int	fd[2];
	int	pid;

	if (!(p->pflag & PF_LAST) && pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		child_signals();
		if (do_redirect(pipe_info->fd_in, fd, p) == -1)
			exit(EXIT_FAILURE);
		if (p->args[0] == NULL || *(p->args[0]) == 0)
			exit(EXIT_FAILURE);
		child(p, runtime, get_builtin(p->args[0]));
	}
	end_pipe(fd, pipe_info, p);
}

// pipe once and and execute all child processes in forks
void	pipex(t_list *list, t_runtime *runtime)
{
	t_pipe	pipe_info;
	int		pid;

	pipe_info.fd_in = -1;
	pipe_info.fd_out = -1;
	close_signals();
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
}
