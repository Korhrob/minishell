/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:58:45 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/20 22:11:00 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// add element as last element in pointer to element lst
void	ft_lstadd_back(t_list **lst, t_list *element)
{
	t_list	*cur;

	if (lst == NULL || element == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = element;
		return ;
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = element;
}
