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


// exits program and unlinks history file
void	ft_exit(int ecode, t_runtime *runtime)
{
	unlink(runtime->history);
	unlink(runtime->heredoc);
	exit(ecode);
}

// execute all commands here
void	do_command(char **args, t_runtime *runtime)
{
	t_process	*child;

	if (ft_quote_check_arr(args) == 0)
	{
		ft_printf("idleshell: unexpected EOF\n");
		ft_exit(2, runtime);
	}
	(void)runtime;
	child = new_process(args);
	if (child == NULL)
		return ;
	if (ft_strcmp(*args, "history") == 0)
		print_history(args + 1, runtime);
	else
	{
		ft_printf("do command %s\n", *args); // debug
		begin_pipe(child);
	}
	clean_process(child);
}

// exectue all builtin commands here
void	do_builtin(char **args, int cmd, t_runtime *runtime)
{
	if (cmd == EXIT)
		ft_exit(0, runtime);
	else if (cmd == PWD)
		cmd_pwd();
	else if (cmd == CD)
		cmd_cd(args, runtime);
	else if (cmd == ENV)
		cmd_env(runtime);
	else if (cmd == UNSET)
		cmd_unset(args[1], runtime);
	else if (cmd == EXPORT)
		cmd_export(args[1], runtime);
	else
		ft_printf("builtin %s\n", *args); // not needed
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
int	execute_args(char **pipes, t_runtime *runtime)
{
	char	**pipe_args;
	int		builtin;

	while (*pipes != NULL)
	{
		// do expansion
		pipe_args = ft_split_quotes(*pipes, ' ', 0);
		if (pipe_args == NULL)
			return (-1);
		if (*pipe_args == 0)
		{
			ft_free_arr(pipe_args);
			return (-1);
		}
		builtin = get_builtin(*pipe_args);
		if (builtin != -1)
			do_builtin(pipe_args, builtin, runtime);
		else
			do_command(pipe_args, runtime);
		//if (*args != NULL) forgot what this is for
		//	args++;
		ft_free_arr(pipe_args);
		pipes++;
	}
	return (-1);
}

// read stdin and split the line
void	shell_interactive(t_runtime *runtime)
{
	char	*line;
	char	**pipes;
	int		status;

	status = -1;
	while (status == -1)
	{
		line = readline("idleshell$ ");
		if (line == NULL)
			break ;
		if (*line == 0)
		{
			free(line);
			continue ;
		}
		record_history(line, runtime);
		pipes = ft_split_quotes(line, '|', 0);
		if (!syntax_error(line) && process_heredoc(line, runtime))
			status = execute_args(pipes, runtime);
		free(line);
		ft_free_arr(pipes);
		unlink(runtime->heredoc);
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

	envi = malloc(sizeof(char *) * (ft_array_len(envp) + 1));
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
	runtime->exepath = get_cwd();
	runtime->history = ft_strjoin(runtime->exepath, "/.history");
	runtime->heredoc = ft_strjoin(runtime->exepath, "/.heredoc");
	unlink(runtime->history);
	unlink(runtime->heredoc);
}

static void	free_runtime(t_runtime *runtime)
{
	ft_free_arr(runtime->env);
	free(runtime->exepath);
	free(runtime->history);
	free(runtime->heredoc);
}

int	main(int argc, char **argv, char **envp)
{
	t_runtime	runtime;

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
	free_runtime(&runtime);
	return (0);
}

// should first split by pipes
// pipe split should respect quotes
// then expand env variables
// then split by spaces

// other stuff to handle
// echo 'asd | zxc' | cat
//<<a cat|cat
//infile<cat|cat>outfile

// if any pipes occur, all commands are done in child
// else if its builtin do it in parent

// should open the pipe before doing anything with children
// keep it open until all children are done
// then close pipe

// note ft_quote_check doesnt work as it should, copy from pipex