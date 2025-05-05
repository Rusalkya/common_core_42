/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:38:38 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/05 13:09:16 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*ncontent;
	void	*content;

	nlst = NULL;
	while (lst)
	{
		content = f(lst->content);
		ncontent = ft_lstnew(content);
		if (!ncontent)
		{
			ft_lstclear(&nlst, del);
			return (NULL);
		}
		ft_lstadd_back(&nlst, ncontent);
		lst = lst->next;
	}
	return (nlst);
}
