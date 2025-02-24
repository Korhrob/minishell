/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:29:40 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 18:29:42 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// prints on standard output all strings from an array except
// the first and any -n flags that remove newline
int	cmd_echo(char **args, int fd)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "-n") == 0)
			i++;
		else
			break ;
	}
	while (args[i] != NULL)
	{
		ft_printf_fd(fd, "%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf_fd(fd, " ");
		i++;
	}
	if (args[1])
	{
		if (ft_strcmp(args[1], "-n") != 0)
			ft_printf_fd(fd, "\n");
	}
	else
		ft_printf_fd(fd, "\n");
	return (0);
}
