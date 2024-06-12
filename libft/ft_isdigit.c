/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:27:34 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/08 14:28:33 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isdigit(unsigned char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// returns 1 if entire string consists of digits
int	ft_isdigit_str(char *str)
{
	while (*str != 0)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
