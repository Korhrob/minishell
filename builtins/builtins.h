#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../minishell.h"

// Builtin commands
void	cmd_pwd();
void	cmd_cd(char **args, t_runtime *runtime);
void	cmd_env(t_runtime *runtime);
void	cmd_unset(char *env, t_runtime *runtime);
void	unset_main(char **args, t_runtime *runtime);
void	cmd_export(char *env, t_runtime *runtime);
void	export_main(char **args, t_runtime *runtime);

// Utility functions
void	free_env(t_env **env);
void    free_single_env(t_env *env);

#endif
