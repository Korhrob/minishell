/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:28:18 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/08 15:52:44 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

// write string s into fd
void	ft_putstr_fd(char *s, int fd)
{
	if (fd == 0 || fd == -1 || s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}
