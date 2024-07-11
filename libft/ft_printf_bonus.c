/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:25:44 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/30 15:28:15 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	ft_get_int(const char *s)
{
	int	num;

	num = 0;
	while (*s >= '0' && *s <= '9')
	{
		num *= 10;
		num += *s - '0';
		s++;
	}
	return (num);
}

static int	ft_int_len(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	ft_print_space(int fd, char c, int size)
{
	int	temp;
	int	count;

	temp = 0;
	count = 0;
	while (size > 0)
	{
		temp = write(fd, &c, 1);
		if (temp < 0)
			return (-1);
		count += temp;
		size--;
	}
	return (count);
}

int	ft_print_nbr_bonus(int fd, const char *s, va_list args, char prefix)
{
	int		count;
	int		size;
	int		n;

	count = 0;
	n = va_arg(args, int);
	size = ft_get_int(s) - ft_int_len(n);
	while (*s >= '0' && *s <= '9')
		s++;
	if (*s != 'd')
		return (-1);
	if (prefix == '0'
		&& ft_add_or_fail(&count, ft_print_space(fd, '0', size)) < 0)
		return (-1);
	if (ft_add_or_fail(&count, ft_print_nbr(fd, n, prefix)) < 0)
		return (-1);
	if (prefix == '-'
		&& ft_add_or_fail(&count, ft_print_space(fd, ' ', size)) < 0)
		return (-1);
	return (count);
}

int	ft_print_str_bonus(int fd, const char *s, va_list args)
{
	int		count;
	int		size;
	char	*str;

	count = 0;
	size = ft_get_int(s);
	while (*s >= '0' && *s <= '9')
		s++;
	if (*s != 's')
		return (-1);
	str = va_arg(args, char *);
	while (*str != 0 && size > 0)
	{
		if (ft_add_or_fail(&count, write(fd, str++, 1)) < 0)
			return (-1);
		size--;
	}
	return (count);
}
