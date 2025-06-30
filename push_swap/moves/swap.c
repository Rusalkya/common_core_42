/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 09:33:44 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/24 09:52:15 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sa(t_node **a, int print)
{
	t_node	*first;
	t_node	*second;

	if ((!a) || (!(*a)) || (!(*a)->next))
		return ;
	first = *a;
	second = first -> next;
	first->next = second->next;
	second->next = first;
	*a = second;
	if (print)
		ft_printf("sa\n");
}

void	sb(t_node **b, int print)
{
	t_node	*first;
	t_node	*second;

	if ((!b) || (!(*b)) || (!(*b)->next))
		return ;
	first = *b;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*b = second;
	if (print)
		ft_printf("sb\n");
}

void	ss(t_node **a, t_node **b, int print)
{
	sa(a, 0);
	sb(b, 0);
	if (print)
		ft_printf("ss\n");
}
