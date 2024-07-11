/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:28:44 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/08 14:29:36 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// c is alphabetical or numerical character
int	ft_isalnum(unsigned char c)
{
	return (ft_isalpha(c) == 1 || ft_isdigit(c) == 1);
}
