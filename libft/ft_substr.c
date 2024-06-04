/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:15:32 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/21 01:02:46 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*out;
	unsigned int	i;
	unsigned int	max;

	if (s == 0)
		return (0);
	max = ft_strlen(s) - start;
	if (ft_strlen(s) < start)
		max = 0;
	if (len > max)
		len = max;
	out = (char *) malloc(len + 1);
	if (out == 0)
		return (0);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (i < len)
		{
			out[i] = s[start + i];
			i++;
		}
	}
	out[i] = 0;
	return (out);
}
