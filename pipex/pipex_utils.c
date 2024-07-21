/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

static int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		perror("stat");
		return (0);
	}
	return (S_ISDIR(statbuf.st_mode));
}

static int	is_executable(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		perror("stat");
		return (0);
	}
	if ((statbuf.st_mode & S_IXUSR) || (statbuf.st_mode & S_IXGRP)
		|| (statbuf.st_mode & S_IXOTH))
		return (1);
	else
		return (0);
}

int	file_checks(t_process *p)
{
	if (!p->path || access(p->path, F_OK) || !is_executable(p->path))
	{
		ft_printf_fd(STDERR_FILENO,
			"idleshell: %s: command not found\n", p->args[0]);
		return (127);
	}
	else if (access(p->path, X_OK))
	{
		ft_printf_fd(STDERR_FILENO,
			"idleshell: %s: no permission\n", p->args[0]);
		return (127);
	}
	else if (is_directory(p->path))
	{
		ft_printf_fd(STDERR_FILENO,
			"idleshell: %s: is a directory\n", p->args[0]);
		return (127);
	}
	return (0);
}
