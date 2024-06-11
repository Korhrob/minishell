#ifndef MINISHELL_H
# define MINISHELL_H

# define BULTIN_CD "cd"
# define BULTIN_ENV "env"
# define BULTIN_HELP "help"
# define BULTIN_EXIT "exit"
# define BULTIN_PWD "pwd"
# define BULTIN_UNSET "unset"
# define BULTIN_EXPORT "export"

typedef enum e_builtin_cmd
{
	CD,
	ENV,
	HELP,
	EXIT,
	PWD,
	UNSET,
	EXPORT
}	t_builtin_cmd;

typedef struct s_runtime
{
	char	**env;
}	t_runtime;

// parse

char	**pipe_cut(char **args);

// history

void	record_history(char *line);
void	print_history(char **args);

// signals

void	signal_signint(int signal);

// readline JANK

extern void	rl_replace_line(const char *, int);

#endif