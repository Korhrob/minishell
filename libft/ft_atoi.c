/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:06:30 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:53:36 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static int	ft_isspace(char *str)
{
	return (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ');
}

// converts a numerical string to int
int	ft_atoi(const char *str)
{
	long long	count;
	int			pos;

	while (ft_isspace((char *)str))
		str++;
	pos = 1;
	if (*str == '-')
		pos *= -1;
	if (*str == '+' || *str == '-')
		str++;
	count = 0;
	while (*str != 0 && ft_isdigit(*str))
	{
		count = count * 10 + (*str - '0');
		if (count < 0)
		{
			if (pos == 1)
				return ((int)LONG_MAX);
			return ((int)LONG_MIN);
		}
		str++;
	}
	return ((int)(count * pos));
}
