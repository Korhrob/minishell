#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "minishell.h"
#include "builtins/builtins.h"

void	ft_exit(int ecode)
{
	unlink(".history");
	exit(ecode);
}

// execute all commands here
// should return how many args we advanced
void	do_command(char **args, t_runtime *runtime)
{
	t_process	*child;

	if (ft_quote_check_arr(args) == 0)
	{
		ft_printf("idleshell: unexpected EOF\n");
		ft_exit(2);
	}
	(void)runtime;
	child = new_process(args);
	if (child == NULL)
		return ;
	if (ft_strcmp(*args, "history") == 0)
		print_history(args + 1);
	ft_printf("do command %s\n", *args);
	clean_process(child);
}

// execute all builtin commands here
// should return how many args we advanced
void	do_builtin(char **args, int cmd, t_runtime *runtime)
{
	if (cmd == EXIT)
		ft_exit(0);
	else if (cmd == PWD)
		cmd_pwd();
	else if (cmd == CD)
		cmd_cd(args, runtime);
	else if (cmd == ENV)
		cmd_env(runtime);
	else if (cmd == UNSET)
		cmd_unset(args[1], runtime);
	else if (cmd == EXPORT)
		export_main(args, runtime);
	else
		ft_printf("builtin %s\n", *args);
}

// gets and returns enum if current string is builtin command
int	get_builtin(char *args)
{
	int			i;
	static char	*builtin[] = {
		BUILTIN_CD,
		BUILTIN_ENV,
		BUILTIN_HELP,
		BUILTIN_EXIT,
		BUILTIN_PWD,
		BUILTIN_UNSET,
		BUILTIN_EXPORT,
	};

	i = 0;
	while (i < BUILTIN_MAX)
	{
		if (ft_strcmp(args, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// execute args 1 by 1
// args are split into sub
int	execute_args(char **args, t_runtime *runtime)
{
	char	**pipe_args;
	int		builtin;

	while (*args != NULL)
	{
		pipe_args = pipe_cut(args);
		if (pipe_args == NULL)
			return (-1);
		builtin = get_builtin(*pipe_args);
		if (builtin != -1)
			do_builtin(pipe_args, builtin, runtime);
		else
			do_command(pipe_args, runtime);
		while (*args != NULL && ft_strcmp(*args, "|") != 0)
			args++;
		if (*args != NULL)
			args++;
		free(pipe_args);
		// wait all children here?
	}
	return (-1);
}

// read stdin and split the line
void	shell_interactive(t_runtime *runtime)
{
	char	*line;
	char	**args;
	int		status;

	status = -1;
	while (status == -1)
	{
		line = readline("idleshell$ ");
		if (line == NULL)
			break ;
		if (*line == 0)
			continue ;
		record_history(line);
		args = ft_split_quotes(line, ' ', 0);
		status = execute_args(args, runtime);
		free(line);
		ft_free_arr(args);
		if (status >= 0)
			exit(status);
	}
}

// probably not needed
void	shell_no_interactive(void)
{

}

// Copies the envp into the runtime struct as an array
static char	**set_env_array(char **envp)
{
	int		i;
	char	**envi;

	envi = malloc(sizeof(char*) * (ft_array_len(envp) + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		envi[i] = ft_strdup(envp[i]);
		i++;
	}
	envi[i] = NULL;
	return (envi);
}

//Initialization of runtime and all the possible content it may have
static void	init_runtime(t_runtime *runtime, char **envp)
{
	runtime->env = set_env_array(envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_runtime	runtime;

	unlink(".history");
	signal_init(0);
	signal(SIGINT, signal_signint);
	signal(SIGTERM, signal_signint);
	runtime.env = NULL;
	if (argc == 1 && argv)
		init_runtime(&runtime, envp);
	if (isatty(STDIN_FILENO) == 1)
		shell_interactive(&runtime);
	else
		shell_no_interactive();
	ft_free_arr(runtime.env);
	return (0);
}
