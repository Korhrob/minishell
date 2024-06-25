#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../minishell.h"

// Builtin pwd
void	cmd_pwd();

// Builtin cd
void	cmd_cd(char **args, t_runtime *runtime);

// Builtin env
void	cmd_env(t_runtime *runtime);

// Builtin unset
void	cmd_unset(char *env, t_runtime *runtime);
void	unset_main(char **args, t_runtime *runtime);

// Builtin export
void	cmd_export(char *env, t_runtime *runtime);
void	export_main(char **args, t_runtime *runtime);

// Builtin echo
void    cmd_echo(char **args);

// Utility functions
void	free_env(t_env **env);
void	free_single_env(t_env *env);
int		create_env(char *envp, t_env *env);
char	*minitrim(char *str, char c);

char	*get_cwd();
char    *str_pwd();

#endif
