/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:33:28 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/20 21:59:33 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// run function del to all list elements pointed by lst
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*next;

	if (lst == NULL)
		return ;
	next = 0;
	cur = *lst;
	while (cur != NULL)
	{
		next = cur->next;
		ft_lstdelone(cur, (del));
		cur = next;
	}
	*lst = 0;
}
