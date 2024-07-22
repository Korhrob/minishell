/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:44:17 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/20 22:10:35 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// add element as last element in pointer to element lst
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

// free list and its nodes
// mode = 0 doesnt free node contents
// mode = 1 free node contents
// return NULL
void	*ft_lst_clean(t_list **list)
{
	t_list	*next;
	t_list	*cur;

	if (list == NULL || *list == NULL)
		return (NULL);
	cur = *list;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->content)
			free(cur->content);
		free(cur);
		cur = next;
	}
	return (NULL);
}
