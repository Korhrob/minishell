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

// return allocated string, copied from s[start] until len, or untill s ends
// if start is outside of s bounds, return empty string
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*out;
	unsigned int	s_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start > s_len)
		len = 0;
	else if (len > (s_len - start))
		len = s_len - start;
	out = (char *) ft_calloc(1, len + 1);
	if (out == 0)
		return (0);
	ft_strlcpy(out, s + start, len + 1);
	return (out);
}
