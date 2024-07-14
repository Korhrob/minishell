/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:52:33 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/20 22:02:01 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// return count of list elements pointed by lst
int	ft_lstsize(t_list *lst)
{
	unsigned int	i;

	i = 0;
	if (lst == 0)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
