/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:09:16 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/13 15:40:51 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	ft_putnbr_recursion(int n, int fd)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr_recursion(n / 10, fd);
	}
	c = '0' + n % 10;
	write(fd, &c, 1);
}

// write nbr n into fd
void	ft_putnbr_fd(int n, int fd)
{
	if (fd == 0 || fd == -1)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	ft_putnbr_recursion(n, fd);
}
