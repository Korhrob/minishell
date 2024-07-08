/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:29:02 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 18:29:03 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "limits.h"
#include <linux/limits.h>

// Fetches the current directory and prints it
void	cmd_pwd(int fd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf_fd(fd, "%s\n", cwd);
	else
		perror("pwd");
}

// gets pwd and returns it as allocated string
char	*str_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*out;

	out = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		out = ft_strdup(cwd);
	else
		perror("pwd");
	return (out);
}
