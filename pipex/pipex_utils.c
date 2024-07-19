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
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int is_directory(const char *path) {
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
	{
		perror("stat");
		return (0);
	}
	return (S_ISDIR(statbuf.st_mode));
}

int is_executable(const char *path) {
	struct stat statbuf;

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
