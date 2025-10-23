/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorg <gorg@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:20:56 by gorg              #+#    #+#             */
/*   Updated: 2024/05/05 18:40:47 by gorg             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*cont;
	void	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		ptr = f(lst->content);
		cont = ft_lstnew(ptr);
		if (!cont)
		{
			del(ptr);
			ft_lstclear(&list, (*del));
			return (list);
		}
		ft_lstadd_back(&list, cont);
		lst = lst->next;
	}
	return (list);
}
