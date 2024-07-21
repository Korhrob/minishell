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

	if (str == NULL || *str == 0)
		return (0);
	size = 0;
	while (*str != 0)
	{
		size++;
		str++;
	}
	return (size);
}

// return len after the first occurance of c, or 1 if not found
size_t	ft_strlen_t(const char *str, char c)
{
	size_t	size;

	if (str == NULL || *str == 0)
		return (0);
	str++;
	size = 1;
	while (*str != 0 && *str != c)
	{
		size++;
		str++;
	}
	if (*str != c)
		return (1);
	return (size + 1);
}
