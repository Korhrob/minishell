/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 03:36:41 by rkorhone          #+#    #+#             */
/*   Updated: 2023/12/04 14:53:37 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	ft_hex_r(int fd, unsigned long n, const char *base, int *count)
{
	int	out;

	out = 0;
	if (n >= 16)
		out = ft_hex_r(fd, n / 16, base, count);
	if (out < 0)
		return (-1);
	out = write(fd, &base[n % 16], 1);
	(*count)++;
	return (out);
}

int	ft_print_hex(int fd, unsigned long n, const char *base, char prefix)
{
	int	count;
	int	error;

	count = 0;
	if (prefix == '#' && n != 0)
		count = write(fd, "0x", 2);
	if (count < 0)
		return (-1);
	error = ft_hex_r(fd, n, base, &count);
	if (error < 0)
		return (-1);
	return (count);
}
