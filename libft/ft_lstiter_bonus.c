/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:57:46 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/20 22:00:36 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// run function f to all list elemets pointed by list
void	ft_lstiter(t_list *list, void (*f)(void *))
{
	t_list	*cur;

	cur = list;
	while (cur != NULL)
	{
		(*f)(cur->content);
		cur = cur->next;
	}
}
