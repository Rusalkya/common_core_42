/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:13:59 by carlos            #+#    #+#             */
/*   Updated: 2025/05/28 11:24:01 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*actuelle;

	if (!lst)
		return (0);
	i = 1;
	actuelle = lst->next;
	while (actuelle != NULL)
	{
		i++;
		actuelle = actuelle->next;
	}
	return (i);
}
