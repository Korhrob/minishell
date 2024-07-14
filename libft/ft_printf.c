/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 23:21:42 by rkorhone          #+#    #+#             */
/*   Updated: 2024/04/09 11:37:41 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	ft_convert_arg(int fd, const char *s, va_list args, char prefix)
{
	int	count;

	if (*s == 0)
		count = 0;
	else if (*s == 'c')
		count = ft_print_chr(fd, va_arg(args, unsigned int));
	else if (*s == 's')
		count = ft_print_str(fd, va_arg(args, char *));
	else if (*s == 'p')
		count = ft_print_ptr(fd, va_arg(args, void *));
	else if (*s == 'd' || *s == 'i')
		count = ft_print_nbr(fd, va_arg(args, int), prefix);
	else if (*s == 'u')
		count = ft_print_nbr_u(fd, va_arg(args, unsigned int));
	else if (*s == 'x')
		count = ft_print_hex(fd, va_arg(args, unsigned int), LOWERCASE, prefix);
	else if (*s == 'X')
		count = ft_print_hex(fd, va_arg(args, unsigned int), UPPERCASE, prefix);
	else if (prefix == '-' || prefix == '0')
		count = ft_print_nbr_bonus(fd, s, args, prefix);
	else if (prefix == '.')
		count = ft_print_str_bonus(fd, s, args);
	else
		count = write(fd, s, 1);
	return (count);
}

static char	ft_move_str(const char **s)
{
	char	prefix;

	prefix = 0;
	(*s)++;
	if (**s == '#' || **s == ' ' || **s == '+')
		prefix = **s;
	else if (**s == '-' || **s == '0' || **s == '.')
		prefix = **s;
	while (**s == prefix)
		(*s)++;
	return (prefix);
}

static void	ft_move_pad(const char **s, char prefix)
{
	if (prefix == '-' || prefix == '0' || prefix == '.')
	{
		while (**s >= '0' && **s <= '9')
			(*s)++;
	}
}

// write string s, with optional arguments %c %s %p %d %u %x %X
// return write length
int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		j;
	char	prefix;

	va_start(args, s);
	i = 0;
	while (*s != 0)
	{
		if (*s == '%')
		{
			prefix = ft_move_str(&s);
			j = ft_convert_arg(1, s, args, prefix);
			ft_move_pad(&s, prefix);
		}
		else
			j = write(1, s, 1);
		if (j < 0)
			return (-1);
		if (*s != 0)
			s++;
		i += j;
	}
	va_end(args);
	return (i);
}

// write string s, with optional arguments %c %s %p %d %u %x %X to fd
// return write length
int	ft_printf_fd(int fd, const char *s, ...)
{
	va_list	args;
	int		i;
	int		j;
	char	prefix;

	va_start(args, s);
	i = 0;
	while (*s != 0)
	{
		if (*s == '%')
		{
			prefix = ft_move_str(&s);
			j = ft_convert_arg(fd, s, args, prefix);
			ft_move_pad(&s, prefix);
		}
		else
			j = write(fd, s, 1);
		if (j < 0)
			return (-1);
		if (*s != 0)
			s++;
		i += j;
	}
	va_end(args);
	return (i);
}
