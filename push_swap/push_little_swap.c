/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_little_swap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:54:22 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/30 15:21:08 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_minimum(t_node *stack)
{
	int			valmin;
	int			posimin;
	int			pos;
	t_node		*current;

	current = stack;
	posimin = 0;
	pos = 0;
	if (!stack)
		return (-1);
	valmin = current->value;
	current = current->next;
	while (current)
	{
		pos++;
		if (current->value < valmin)
		{
			valmin = current->value;
			posimin = pos;
		}
		current = current->next;
	}
	return (posimin);
}

void	sort_three(t_node **a)
{
	int		first;
	int		second;
	int		third;

	first = (*a)->value;
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	if (first > second && second < third && first < third)
		sa(a, 1);
	else if (first > second && second > third)
	{
		sa(a, 1);
		rra(a, 1);
	}
	else if (first > second && second < third && first > third)
		ra(a, 1);
	else if (first < second && second > third && first < third)
	{
		sa(a, 1);
		ra(a, 1);
	}
	else if (first < second && second > third && first > third)
		rra(a, 1);
}

void	sort_small_stack(t_node **a, t_node **b)
{
	int	posimin;

	while (ft_stacksize(*a) > 3)
	{
		posimin = find_minimum(*a);
		if (posimin <= ft_stacksize(*a) / 2)
		{
			while (posimin-- > 0)
				ra(a, 1);
		}
		else
		{
			posimin = ft_stacksize(*a) - posimin;
			while (posimin-- > 0)
				rra(a, 1);
		}
		pb(a, b, 1);
	}
	sort_three(a);
	while (*b)
		pa(a, b, 1);
}

void	push_little_swap(t_node **a, t_node **b)
{
	int		size;

	if (is_sorted(*a))
		return ;
	size = ft_stacksize(*a);
	if (size == 2)
		sa(a, 1);
	else if (size == 3)
		sort_three(a);
	else if (size > 3 && size <= 5)
		sort_small_stack(a, b);
}
