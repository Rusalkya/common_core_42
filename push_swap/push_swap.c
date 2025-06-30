/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:35:05 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/30 15:13:22 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_max_bits(t_node *stack)
{
	int		max;
	int		bits;

	if (!stack)
		return (0);
	max = stack->value;
	while (stack)
	{
		if (stack->value > max)
			max = stack->value;
		stack = stack->next;
	}
	bits = 0;
	while ((1 << bits) <= max)
		bits++;
	return (bits);
}

static int	handle_invalid_input(char **args, t_node **a)
{
	ft_putstr_fd("Error\n", 2);
	free_split(args);
	free_stack(a);
	return (0);
}

void	choose_sort(t_node **a, t_node **b, int size)
{
	if (size <= 5)
		push_little_swap(a, b);
	else
		radix_sort(a, b);
}

int	init_args_and_stack(int argc, char **argv, char ***args, t_node **a)
{
	*args = get_args_split(argc, argv);
	if (!*args)
		return (0);
	parse_args_to_stack(*args, a);
	if (!parsing_is_valid(*args, *a))
		return (0);
	return (1);
}

void	push_swap(int argc, char **argv)
{
	t_node	*a;
	t_node	*b;
	char	**args;
	int		size;

	if (argc < 2)
		return ;
	a = NULL;
	b = NULL;
	if (!init_args_and_stack(argc, argv, &args, &a))
	{
		handle_invalid_input(args, &a);
		return ;
	}
	free_split(args);
	apply_normalization(a);
	size = ft_stacksize(a);
	if (is_sorted(a) || size < 2)
	{
		free_stack(&a);
		return ;
	}
	choose_sort(&a, &b, size);
	free_stack(&a);
}
