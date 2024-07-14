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

static char	*get_value_fake(char *str)
{
	// get the end value with key STR
	return NULL;
}

static int	expand_logic(char *str, char *out)
{
	int	pos;
	int	next;
	int	i;
	int	quotes;

	pos = ft_strchr(str, '$');
	if (pos == 0)
		return (0);
	while (pos != 0)
	{
		i = 0;
		while (pos - i > 0)
			if (str[pos - 1] == '\'')
				quotes++;
		if (quotes % 2 == 0)
		{
			if (out == NULL) 
				out = ft_strdup(get_value_fake(str + pos));
			else
				ft_strjoin(out, get_value_fake(str + pos));
			if (out == NULL)
				return (-1);
		}
		pos += get_key_len(str + pos);
		next = ft_strchr(str + pos + 1, '$');
		if (next - pos > 0)
		{
			
		}
	}
}


asd$pwd/fdsfdfds$pwd

// iterates the pipe and creates an array with expandable portions
// replaced with corresponding environment values
char	**create_strings(char **splitpipe, char *pipe, t_env **environ)
{
	int		i;
	char	**arr;

	i = 0;
	arr = ft_split_quotes(pipe, ' ', 0);
	while (arr[i] != NULL)
	{
		if (expand_logic(arr[i], splitpipe[i]))
		{
			//
		}
		else
		{
			splitpipe[i] = ft_strdup(arr[i]);
		}
		if (splitpipe[i] == NULL)
		{
			// malloc fail
		}
		i++;
	}

	/*
	int	i;
	int	len;

	i = 0;
	len = 0;


	while (*pipe != 0)
	{
		if ((*pipe == '$') && (*(pipe + 1) != '$' || *(pipe - 1) != '$'))
		{
			splitpipe[i] = ft_strldup(pipe - len, 0, len);
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
	*/
	return (splitpipe);
}

// echo $PWD > out