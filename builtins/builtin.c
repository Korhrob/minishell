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
#include <errno.h>

static int	ft_exit(t_process *p, t_runtime *runtime)
{
	int	ecode;

	ecode = EXIT_SUCCESS;
	if (p->args[1] && !ft_isdigit_str(p->args[1]))
	{
		ecode = 2;
		errno = 2;
		ft_printf_fd(STDERR_FILENO,
			"idleshell: exit: numeric argument required\n");
		ft_itoa_buf(runtime->errorcode, 2);
	}
	if (p->args[1])
		ecode = ft_atoi(p->args[1]);
	ft_printf_fd(STDOUT_FILENO, "exit\n");
	free_runtime(runtime);
	exit(ecode);
}

// exectue all builtin commands here
// should return int back to main
int	do_builtin(t_process *p, int cmd, t_runtime *runtime, int fd)
{
	int	ret;

	if (cmd == EXIT)
		ft_exit(p, runtime);
	else if (cmd == PWD)
		ret = cmd_pwd(fd);
	else if (cmd == CD)
		ret = cmd_cd(p->args, runtime);
	else if (cmd == ENV)
		ret = cmd_env(runtime, fd);
	else if (cmd == UNSET)
		ret = unset_main(p->args, runtime);
	else if (cmd == EXPORT)
		ret = export_main(p->args, runtime, fd);
	else if (cmd == ECHO)
		ret = cmd_echo(p->args, fd);
	else if (cmd == HISTORY)
		ret = print_history((p->args + 1), runtime, fd);
	if (runtime->exit_status == MALLOC_FAIL)
	{
		free_runtime(runtime);
		exit(runtime->exit_status);
	}
	ft_itoa_buf(runtime->errorcode, ret);
	return (ret);
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
		fd = open(process->outfile, process->outflag, 0777);
		if (fd == -1)
			return (EXIT_FAILURE);
	}
	builtin = get_builtin(process->args[0]);
	return_flag = do_builtin(process, builtin, runtime, fd);
	if (process->outfile != NULL)
		close(fd);
	return (return_flag);
}
