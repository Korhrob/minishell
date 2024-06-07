/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:34:42 by rkorhone          #+#    #+#             */
/*   Updated: 2023/11/20 22:01:46 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*obj;

	obj = (t_list *) malloc(sizeof(t_list));
	if (obj == 0)
		return (0);
	obj->content = content;
	obj->next = 0;
	return (obj);
}
