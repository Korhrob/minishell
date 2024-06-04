/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:48:08 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:59 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*out;
	unsigned int	i;
	unsigned int	len;

	if (s == 0)
		return (0);
	len = ft_strlen(s);
	out = (char *) malloc(len + 1);
	if (out == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		out[i] = (*f)(i, s[i]);
		i++;
	}
	out[i] = 0;
	return (out);
}
