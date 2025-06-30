/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:06:40 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/27 12:16:19 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*sort_int_tab(int *tab, int size)
{
	int	i;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (tab);
}

int	*normalize_stack(t_node *stack)
{
	int		count;
	int		i;
	int		*pile;

	count = ft_stacksize(stack);
	i = 0;
	pile = malloc(sizeof (int) * (count));
	if (!pile)
		return (NULL);
	while (stack)
	{
		pile[i] = stack->value;
		stack = stack->next;
		i++;
	}
	sort_int_tab(pile, count);
	return (pile);
}

int	find_index(int *array, int value, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (array[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

void	update_stack_values(t_node *stack, int *sorted, int size)
{
	int	index;

	while (stack)
	{
		index = find_index(sorted, stack->value, size);
		if (index != -1)
			stack->value = index;
		stack = stack->next;
	}
}

void	apply_normalization(t_node *stack)
{
	int	*sorted;
	int	size;

	size = ft_stacksize(stack);
	sorted = normalize_stack(stack);
	if (!sorted)
		return ;
	sort_int_tab(sorted, size);
	update_stack_values(stack, sorted, size);
	free(sorted);
}
