/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:51:01 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/24 09:51:41 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ra(t_node **a, int print)
{
	t_node	*first;
	t_node	*last;

	if ((!a) || (!(*a)) || (!(*a)->next))
		return ;
	first = *a;
	last = *a;
	while (last->next)
		last = last->next;
	*a = first->next;
	first->next = NULL;
	last->next = first;
	if (print)
		ft_printf("ra\n");
}

void	rb(t_node **b, int print)
{
	t_node	*first;
	t_node	*last;

	if ((!b) || (!(*b)) || (!(*b)->next))
		return ;
	first = *b;
	last = *b;
	while (last->next)
		last = last->next;
	*b = first->next;
	first->next = NULL;
	last->next = first;
	if (print)
		ft_printf("rb\n");
}

void	rr(t_node **a, t_node **b, int print)
{
	ra(a, 0);
	rb(b, 0);
	if (print)
		ft_printf("rr\n");
}
