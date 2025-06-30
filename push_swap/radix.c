/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:47:43 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/27 11:52:00 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	radix_pass(t_node **a, t_node **b, int bit)
{
	int	size;
	int	value;
	int	i;

	i = 0;
	size = ft_stacksize(*a);
	while (i < size)
	{
		value = (*a)->value;
		if (((value >> bit) & 1) == 0)
			pb(a, b, 1);
		else
			ra(a, 1);
		i++;
	}
}

void	restore_stack(t_node **a, t_node **b)
{
	int	n;

	n = ft_stacksize(*b);
	while (n-- > 0)
		pa(a, b, 1);
}

void	radix_sort(t_node **a, t_node **b)
{
	int	i;
	int	max_bits;

	i = 0;
	max_bits = get_max_bits(*a);
	while (i < max_bits)
	{
		radix_pass(a, b, i);
		restore_stack(a, b);
		i++;
	}
}
