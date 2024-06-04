/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:38:10 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:50 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// return len till null terminator
size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	if (str == NULL || *str == 0)
		return (size);
	while (*str != 0)
	{
		size++;
		str++;
	}
	return (size);
}

// return len till next occurance of first char in str
size_t	ft_strlen_c(const char *str)
{
	size_t	size;
	char	c;

	if (str == NULL || *str == 0)
		return (0);
	c = str[0];
	size = 1;
	while (str[size] != 0 && str[size] != c)
		size++;
	if (str[size] == c)
		size++;
	return (size);
}

// return len till first occurance of c
size_t	ft_strlen_t(const char *str, char c)
{
	size_t	size;

	size = 0;
	if (str == NULL || *str == 0)
		return (size);
	while (*str != 0 && *str != c)
	{
		size++;
		str++;
	}
	return (size);
}
