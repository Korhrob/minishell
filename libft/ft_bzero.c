/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:10:02 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/11 13:56:23 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// memset ptr s to 0 for n length
void	ft_bzero(void *s, size_t n)
{
	ft_memset((void *) s, 0, n);
}
