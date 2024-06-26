#ifndef MINISHELL_H
# define MINISHELL_H

# define BUILTIN_CD "cd"
# define BUILTIN_ENV "env"
# define BUILTIN_HELP "help"
# define BUILTIN_EXIT "exit"
# define BUILTIN_PWD "pwd"
# define BUILTIN_UNSET "unset"
# define BUILTIN_EXPORT "export"
# define BUILTIN_ECHO "echo"

extern int g_exit_status;

typedef enum e_builtin_cmd
{
	CD,
	ENV,
	HELP,
	EXIT,
	PWD,
	UNSET,
	EXPORT,
	ECHO,
	BUILTIN_MAX
}	t_builtin_cmd;

typedef enum e_error_code
{
	SUCCESS,
	FAIL,
	MALLOC_FAIL
}	t_error_code;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_runtime
{
	char	**env;
	t_env	**env_struct;
	int		err_num;
	//t_list	**child_pid;
}	t_runtime;

typedef struct s_process
{
	char	*infile;
	char	*outfile;
	char	**args;
}	t_process;


// parse

char		**pipe_cut(char **args);

// history

void		record_history(char *line);
void		print_history(char **args);

// signals

void		signal_init(int flag);
void		signal_signint(int signo);
void		signal_reset(void);

// readline JANK

void		rl_replace_line(const char *str, int i);

// pipes
t_process	*new_process(char **args);
void		clean_process(t_process *p);
void		set_inout(t_process *p);

// heredoc
char		*ft_heredoc(int flag, char *delimit);

// Environment

t_env	**set_env_struct(char **envp);

#endif