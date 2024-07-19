/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:16:00 by avegis            #+#    #+#             */
/*   Updated: 2024/07/19 16:16:01 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <fcntl.h>

// exectue all builtin commands here
// should return int back to main
int	do_builtin(t_process *p, int cmd, t_runtime *runtime, int fd)
{
	if (cmd == EXIT)
		return (1);
	else if (cmd == PWD)
		cmd_pwd(fd);
	else if (cmd == CD)
		cmd_cd(p->args, runtime);
	else if (cmd == ENV)
		cmd_env(runtime, fd);
	else if (cmd == UNSET)
		unset_main(p->args, runtime);
	else if (cmd == EXPORT)
		export_main(p->args, runtime, fd);
	else if (cmd == ECHO)
		cmd_echo(p->args, fd);
	else if (cmd == HISTORY)
		print_history((p->args + 1), runtime, fd);
	return (-1);
}

// gets and returns enum if current string is builtin command
int	get_builtin(char *args)
{
	int			i;
	static char	*builtin[] = {
		BUILTIN_NONE,
		BUILTIN_CD,
		BUILTIN_ENV,
		BUILTIN_HELP,
		BUILTIN_EXIT,
		BUILTIN_PWD,
		BUILTIN_UNSET,
		BUILTIN_EXPORT,
		BUILTIN_ECHO,
		BUILITIN_HISTORY
	};

	if (args == NULL)
		return (0);
	i = 1;
	while (i < BUILTIN_MAX)
	{
		if (ft_strcmp(args, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

// execute single builtin in parent
int	single_builtin(t_process *process, t_runtime *runtime)
{
	int	fd;
	int	builtin;
	int	return_flag;

	fd = STDOUT_FILENO;
	return_flag = -1;
	if (process->outfile != NULL)
	{
		fd = open(process->outfile, process->outflag, 0644);
		if (fd == -1)
			return (EXIT_FAILURE);
	}
	builtin = get_builtin(process->args[0]);
	return_flag = do_builtin(process, builtin, runtime, fd);
	if (process->outfile != NULL)
		close(fd);
	return (return_flag);
}
