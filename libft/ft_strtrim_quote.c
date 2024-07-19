/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtim_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:07:23 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:51:26 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static size_t	ft_trim_len(const char *str)
{
	int		i;
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
				continue ;
			}
		}
		i++;
		str++;
	}
	return (i);
}

// trims outer quotes from str and returns a new string, 
// should return NULL on allocation failure
char	*ft_strtrim_quote(const char *str)
{
	char	*out;
	char	*ptr;
	size_t	len;

	len = ft_trim_len(str);
	out = (char *)ft_calloc(1, len + 1);
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
				out += ft_strncpy(out, str + 1, len - 2);
				str += len;
				continue ;
			}
		}
		*out++ = *str++;
	}
	return (ptr);
}

// create a copy of an array and trim paired quotes from all strings in array
// if flag is set, free the original array before returning
char	**ft_strtrim_quote_arr(char **arr, int flag)
{
	char	**out;
	int		i;

	if (arr == NULL || *arr == NULL)
		return (arr);
	out = (char **) ft_calloc(sizeof(char *), ft_array_len((void *)arr) + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		out[i] = ft_strtrim_quote(arr[i]);
		if (!out[i])
		{
			ft_printf_fd(STDERR_FILENO, "malloc fail\n");
			ft_free_arr(out);
			return (NULL);
		}
		i++;
	}
	if (flag)
		ft_free_arr(arr);
	return (out);
}
