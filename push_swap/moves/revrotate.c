/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   revrotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:00:18 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/24 09:41:33 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	rra(t_node **a, int print)
{
	t_node	*last;
	t_node	*prelast;

	if (!a || (!(*a)) || (!(*a)->next))
		return ;
	last = *a;
	prelast = NULL;
	while (last->next)
	{
		prelast = last;
		last = last->next;
	}	
	prelast->next = NULL;
	last->next = *a;
	*a = last;
	if (print)
		ft_printf("rra\n");
}

void	rrb(t_node **b, int print)
{
	t_node	*last;
	t_node	*prelast;

	if (!b || (!(*b)) || (!(*b)->next))
		return ;
	last = *b;
	prelast = NULL;
	while (last->next)
	{
		prelast = last;
		last = last->next;
	}	
	prelast->next = NULL;
	last->next = *b;
	*b = last;
	if (print)
		ft_printf("rrb\n");
}

void	rrr(t_node **a, t_node **b, int print)
{
	rra(a, 0);
	rrb(b, 0);
	if (print)
		ft_printf("rrr\n");
}
