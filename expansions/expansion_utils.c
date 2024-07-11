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
#include <stdlib.h>
#include <stdio.h>

// free every second string in the array starting with first
void	*free_expands(char **array, int index)
{
	int	i;

	i = 0;
	if (index > 0)
		array[index] = NULL;
	while (array[i] != NULL)
	{
		free(array[i]);
		if (array[i + 1] != NULL)
			i++;
		i++;
	}
	free(array);
	return (NULL);
}

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

// iterates the pipe and creates an array with expandable portions
// replaced with corresponding environment values
char	**create_strings(char **splitpipe, char *pipe, t_env **environ)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (*pipe != 0)
	{
		if ((*pipe == '$') && (*(pipe + 1) != '$' || *(pipe - 1) != '$'))
		{
			splitpipe[i] = ft_strndup(pipe - len, 0, len);
			if (!splitpipe[i])
				return (free_expands(splitpipe, i));
			splitpipe[i + 1] = expand(pipe + 1, environ);
			while (ft_isalnum(*(pipe + 1))
				|| *(pipe + 1) == '-' || *(pipe + 1) == '_')
				pipe++;
			i = i + 2;
			len = -1;
		}
		len++;
		pipe++;
	}
	splitpipe[i] = NULL;
	return (splitpipe);
}

// echo $PWD > out