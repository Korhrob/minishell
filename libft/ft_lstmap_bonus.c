/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:59:37 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/20 22:01:32 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	void	*temp;
	t_list	*start;
	t_list	*cur;

	temp = NULL;
	start = NULL;
	while (lst != NULL)
	{
		if (f)
			temp = f(lst->content);
		cur = ft_lstnew(temp);
		if (cur == 0)
		{
			ft_lstclear(&start, del);
			free(temp);
			return (0);
		}
		ft_lstadd_back(&start, cur);
		lst = lst->next;
	}
	return (start);
}
