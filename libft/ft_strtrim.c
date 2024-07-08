/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:05:39 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:32 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_arrcmp(const char c, const char *set)
{
	while (*set != 0)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static void	ft_len(const char *s1, const char *set, int *start, int *end)
{
	while (*start < *end)
	{
		if (ft_arrcmp(s1[*start], set) == 0)
			break ;
		(*start)++;
	}
	while (*end > *start)
	{
		if (ft_arrcmp(s1[*end - 1], set) == 0)
			break ;
		(*end)--;
	}
}

// trim all characters in set from start and end of s1
char	*ft_strtrim(const char *s1, const char *set)
{
	char	*out;
	int		start;
	int		end;
	int		i;

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	ft_len(s1, set, &start, &end);
	out = (char *) malloc(end - start + 1);
	if (out == 0)
		return (0);
	i = 0;
	while (i < end - start)
	{
		out[i] = s1[start + i];
		i++;
	}
	out[i] = 0;
	return (out);
}

static int	ft_trim_len(const char *str)
{
	int	i;

	i = 0;
	while (*str != 0)
	{
		if (*str == '\'' || *str == '\"')
		{
			i += ft_strlen_t(str, *str);
			str += ft_strlen_t(str, *str) + 1;
		}
		else
		{
			i++;
			str++;
		}
	}
	return (i);
}

// trims outer quotes from str and returns a new string
// TODO: test this
char	*ft_strtrim_quote(const char *str)
{
	char	*out;
	char	*ptr;
	int		i;

	out = (char *)ft_calloc(1, i + 1);
	if (!out)
		return (str);
	ptr = out;
	while (*str != 0)
	{
		if (*str == '\'' || *str == '\"')
		{
			i = ft_strlen_t(str + 1, *str);
			out += ft_strlcpy(out, str + 1, i + 1);
			str += i + 1;
		}
		else
		{
			*out = *str;
			out++;
			str++;
		}
	}
	return (ptr);
}

	/* OLD
	len = ft_strlen(str);
	if (len == 0)
		return (NULL);
	c = 0;
	if (str[len - 1] == '\'' || str[len - 1] == '\"')
		c = str[len - 1];
	if (str[0] == c)
	{
		str++;
		len -= 2;
	}
	out = (char *)malloc(len + 1);
	if (out == NULL)
		return (NULL);
	ft_strlcpy(out, str, len + 1);
	return (out);
	*/
