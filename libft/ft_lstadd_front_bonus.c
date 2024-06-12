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

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

// creates an empty list
t_list	**ft_lst_create(void)
{
	t_list	**list;

	list = (t_list **) malloc(sizeof(t_list *));
	if (list == NULL)
		return (NULL);
	*list = NULL;
	return (list);
}

// free list and its nodes
// mode = 0 doesnt free node contents
// mode = 1 free node contents
// always returns NULL
void	*ft_lst_clean(t_list **list, int mode)
{
	t_list	*next;
	t_list	*cur;

	if (list == NULL || *list == NULL)
		return (NULL);
	cur = *list;
	while (cur != NULL)
	{
		next = cur->next;
		if (mode)
			free(cur->content);
		free(cur);
		cur = next;
	}
	free(list);
	return (NULL);
}
