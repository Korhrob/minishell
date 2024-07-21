/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

// if c is any character in set return 1
int	is_charset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*unquote_filename(char *str)
{
	char	*out;

	out = ft_strtrim_quote(str);
	free(str);
	if (!out)
		return (NULL);
	return (out);
}

// moves str to first char after << < or >
// then gets length until next syntax symbol or space
// then copies the chars until that point into a new string
char	*get_filename(char *str)
{
	char	*out;
	int		len;

	while (*str == ' ')
		str++;
	len = 0;
	while (str[len] != 0)
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			len += ft_strlen_t(str + len, str[len]);
			continue ;
		}
		if (is_charset(str[len], "|<> "))
			break ;
		len++;
	}
	out = (char *) malloc(len + 1);
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, str, len + 1);
	out = unquote_filename(out);
	return (out);
}
