/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:19:05 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:40:31 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_countlen(int i)
{
	int	len;

	len = 0;
	if (i == 0)
		return (1);
	if (i < 0)
		len++;
	while (i != 0)
	{
		i /= 10;
		len++;
	}
	return (len);
}

static void	ft_recursion(int i, char *s, int *depth)
{
	if (i > 9)
		ft_recursion(i / 10, s, depth);
	s[(*depth)++] = (i % 10) + '0';
}

char	*ft_itoa(int i)
{
	char	*s;
	int		depth;

	s = (char *) malloc(ft_countlen(i) + 1);
	if (s == 0)
		return (0);
	if (i == -2147483648)
	{
		ft_strlcpy(s, "-2147483648\0", (unsigned int) 12);
		return (s);
	}
	depth = 0;
	if (i < 0)
	{
		i = -i;
		s[depth++] = '-';
	}
	ft_recursion(i, s, &depth);
	s[depth] = 0;
	return (s);
}
