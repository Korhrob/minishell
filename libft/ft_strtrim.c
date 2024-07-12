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

//#include <unistd.h>

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

	if (s1 == 0 || set == 0)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	ft_len(s1, set, &start, &end);
	out = (char *) ft_calloc(1, end - start + 1);
	if (out == 0)
		return (0);
	ft_strlcpy(out, s1 + start, end - start + 1);
	return (out);
}

static size_t	ft_trim_len(const char *str)
{
	int	i;
	size_t	len;

	i = 0;
	while (*str != 0)
	{
		if (*str == '\'' || *str == '\"')
		{
			len = ft_strlen_t(str, *str);
			if (len >= 2)
			{
				i += len - 2;
				str += len;
				continue;
			}
		}
		i++;
		str++;
	}
	return (i);
}

// trims outer quotes from str and returns a new string, should return NULL on allocation failure
// TODO: double tripple test this
char	*ft_strtrim_quote(const char *str)
{
	char	*out;
	char	*ptr;
	//char	*debug = (char *)str;
	size_t	len;

	len = ft_trim_len(str);
	out = (char *)ft_calloc(1, len + 1);
	//ft_printf_fd(STDERR_FILENO, "calloc %d + 1, size %d\n", len, sizeof(out));
	if (!out)
		return (NULL);
	ptr = out;
	while (*str != 0)
	{
		if (*str == '\'' || *str == '\"')
		{
			len = ft_strlen_t(str, *str);
			if (len >= 2)
			{
				//ft_printf_fd(STDERR_FILENO, "strncpy [%s] %d\n", str, len - 2);
				out += ft_strncpy(out, str + 1, len - 2);
				str += len;
				continue;
			}
		}
		//ft_printf_fd(STDERR_FILENO, "strncpy [%c]\n", *str);
		*out++ = *str++;
	}
	//ft_printf_fd(STDERR_FILENO, "original [%s]\ntrimmed [%s]\n\n", debug, ptr);
	return (ptr);
}
