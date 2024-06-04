/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:06:12 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:12 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// return first occurance of c or 0 if not found in string
char	*ft_strchr(const char *s, int c)
{
	while (*s != 0)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *) s);
		s++;
	}
	if (*s == '\0' && (char)c == '\0')
		return ((char *)(s));
	return (0);
}

// return str after next occurance of c after the first char
char	*ft_strchr_q(const char *str, int c)
{
	str++;
	while (*str != 0)
	{
		while (*str != 0 && *str != c)
			str++;
		if (*str != 0)
			return ((char *)++str);
	}
	return ((char *)str);
}
