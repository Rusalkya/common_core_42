/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:49:05 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/05 11:01:18 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

/*
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	del_str(void *content)
{
	free(content);
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int	main(void)
{
	t_list	*list;

	list = ft_lstnew(ft_strdup("Hello"));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("World")));
	ft_lstadd_back(&list, ft_lstnew(ft_strdup("!")));
	printf("Liste avant clear :\n");
	print_list(list);
	ft_lstclear(&list, del_str);
	if (list == NULL)
		printf("Liste après clear : OK (liste = NULL)\n");
	else
		printf("Erreur : liste non NULL après clear\n");
	return (0);
}
*/