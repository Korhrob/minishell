/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:30:00 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 18:30:01 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../minishell.h"

// Builtin
int		do_builtin(t_process *p, int cmd, t_runtime *runtime, int fd);
int		get_builtin(char *args);
int		single_builtin(t_process *process, t_runtime *runtime);

// Builtin pwd
void	cmd_pwd(int fd);

// Builtin cd
void	cmd_cd(char **args, t_runtime *runtime);

// Builtin env
void	cmd_env(t_runtime *runtime, int fd);

// Builtin unset
int		cmd_unset(char *env_line, t_runtime *runtime);
void	unset_main(char **args, t_runtime *runtime);

// Builtin export
int		cmd_export(char *env, t_runtime *runtime);
void	export_main(char **args, t_runtime *runtime, int fd);

// Builtin echo
void	cmd_echo(char **args, int fd);

// Utility functions
void	free_env(t_env **env);
void	free_single_env(t_env *env);
int		export_malloc_fail(t_env **array, t_env *node);
int		create_env(char *envp, t_env *env);
char	*minitrim(char *str, char c);

char	*get_cwd(void);
char	*str_pwd(void);

#endif
