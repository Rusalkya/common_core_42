/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:06:58 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/30 15:17:58 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	pa(t_node **a, t_node **b, int print)
{
	t_node	*bfirst;

	if (!b || !(*b))
		return ;
	bfirst = *b;
	*b = (*b)->next;
	bfirst->next = *a;
	*a = bfirst;
	if (print)
		ft_printf("pa\n");
}

void	pb(t_node **a, t_node **b, int print)
{
	t_node	*afirst;

	if ((!a) || (!(*a)))
		return ;
	afirst = *a;
	*a = (*a)->next;
	afirst->next = *b;
	*b = afirst;
	if (print)
		ft_printf("pb\n");
}
