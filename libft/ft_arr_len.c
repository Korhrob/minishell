/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avegis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:52:22 by avegis            #+#    #+#             */
/*   Updated: 2024/07/08 19:52:25 by avegis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Counts the number of strings inside an array
int	ft_array_len(void **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (i);
	while (*array != NULL)
	{
		i++;
		array++;
	}
	return (i);
}
