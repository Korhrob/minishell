/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 03:36:41 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/30 14:56:43 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	ft_add_prefix(int fd, int n, char prefix)
{
	int	count;

	count = 0;
	if (n < 0)
		count = write(fd, "-", 1);
	else if (prefix == '+' && n > 0)
		count = write(fd, "+", 1);
	else if (prefix == ' ' && n > 0)
		count = write(fd, " ", 1);
	return (count);
}

static int	ft_print_nbr_recursion(int fd, unsigned int n, int *count)
{
	char	c;
	int		out;

	out = 0;
	if (n > 9)
		out = ft_print_nbr_recursion(fd, n / 10, count);
	if (out < 0)
		return (-1);
	c = '0' + n % 10;
	out = write(fd, &c, 1);
	(*count)++;
	return (out);
}

// write int to fd
int	ft_print_nbr(int fd, int n, char prefix)
{
	int	count;
	int	error;

	count = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	count = ft_add_prefix(fd, n, prefix);
	if (n < 0)
		n = -n;
	if (count < 0)
		return (-1);
	error = ft_print_nbr_recursion(fd, n, &count);
	if (error < 0)
		return (-1);
	return (count);
}

int	ft_print_nbr_u(int fd, unsigned int n)
{
	int	count;
	int	error;

	count = 0;
	error = ft_print_nbr_recursion(fd, n, &count);
	if (error < 0)
		return (-1);
	return (count);
}
