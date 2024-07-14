/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:53:06 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 19:53:07 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

// using the key finds the correct value if it exists
static char	*find_expansion(char *key, t_env **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strcmp(environ[i]->key, key) == 0)
		{
			free (key);
			return (environ[i]->value);
		}
		i++;
	}
	return (NULL);
}

// Creates the key for which were looking for in the environ
static char	*expand(char *pipe, t_env **environ)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (ft_isalnum(pipe[i]) || pipe[i] == '-' || pipe[i] == '_')
		i++;
	key = (char *)malloc(i + 1);
	ft_strlcpy(key, pipe, i + 1);
	return (find_expansion(key, environ));
}

static int	create_duo(t_exp *exp, t_env **environ, char **splitpipe)
{
	if ((*exp->pipe == '$') && (*(exp->pipe + 1) != '$'
			|| *(exp->pipe - 1) != '$'))
	{
		splitpipe[exp->i] = ft_strndup(exp->pipe - exp->len, 0, exp->len);
		if (!splitpipe[exp->i])
		{
			free_expands(splitpipe, exp->i);
			return (MALLOC_FAIL);
		}
		splitpipe[exp->i + 1] = expand(exp->pipe + 1, environ);
		while (ft_isalnum(*(exp->pipe + 1))
			|| *(exp->pipe + 1) == '-' || *(exp->pipe + 1) == '_')
			exp->pipe++;
		exp->i = exp->i + 2;
		exp->len = -1;
	}
	return (SUCCESS);
}

void	iterate(t_exp *exp)
{
	if (*exp->pipe == '\'')
	{
		exp->pipe += ft_strlen_t(exp->pipe, '\'');
		exp->len += ft_strlen_t(exp->pipe, '\'');
		return ;
	}
	exp->len++;
	exp->pipe++;
}

// iterates the pipe and creates an array with expandable portions
// replaced with corresponding environment values
char	**create_strings(char **splitpipe, char *pipe, t_env **environ)
{
	t_exp	exp;

	exp.i = 0;
	exp.len = 0;
	exp.pipe = pipe;
	while (*exp.pipe != 0)
	{
		if (create_duo(&exp, environ, splitpipe) == MALLOC_FAIL)
			return (NULL);
		iterate(&exp);
	}
	if (exp.len > 0)
		splitpipe[exp.i++] = ft_strndup(exp.pipe - exp.len, 0, exp.len);
	if (!splitpipe[exp.i - 1])
	{
		free_expands(splitpipe, exp.i - 1);
		return (NULL);
	}
	splitpipe[exp.i] = NULL;
	return (splitpipe);
}
