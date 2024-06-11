#ifndef MINISHELL_H
# define MINISHELL_H

# define BUILTIN_CD "cd"
# define BUILTIN_ENV "env"
# define BUILTIN_HELP "help"
# define BUILTIN_EXIT "exit"
# define BUILTIN_PWD "pwd"
# define BUILTIN_UNSET "unset"
# define BUILTIN_EXPORT "export"

typedef enum e_builtin_cmd
{
	CD,
	ENV,
	HELP,
	EXIT,
	PWD,
	UNSET,
	EXPORT,
	BUILTIN_MAX
}	t_builtin_cmd;

typedef struct s_runtime
{
	char	**env;
	t_list	**child_pid;
}	t_runtime;

typedef struct s_process
{
	char	**args;
	char	*infile;
	char	*outfile;
}	t_process;

// parse

char	**pipe_cut(char **args);

// history

void	record_history(char *line);
void	print_history(char **args);

// signals

void	signal_signint(int signal);

// readline JANK

extern void	rl_replace_line(const char *, int);

// pipes
t_process	*new_process(char **args);

#endif