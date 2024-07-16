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

// c is numerical character
int	ft_isdigit(unsigned char c)
{
	return (c >= '0' && c <= '9');
}

// str contains only numerical characters
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
