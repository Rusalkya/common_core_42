/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:10:42 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/27 11:56:44 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*create_node(int value)
{
	t_node	*new_node;

	new_node = malloc(sizeof (t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	append_node(t_node **stack, t_node *new_node)
{
	t_node	*current;

	if (!stack || !new_node)
		return ;
	if (*stack == NULL)
	{
		*stack = new_node;
		return ;
	}
	current = *stack;
	while (current -> next)
		current = current->next;
	current->next = new_node;
}

void	print_stack(t_node *stack)
{
	while (stack)
	{
		ft_printf("%d\n", stack->value);
		stack = stack->next;
	}
}

void	free_stack(t_node **stack)
{
	t_node	*temp;

	if (!stack)
		return ;
	while (*stack)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
	*stack = NULL;
}

int	ft_stacksize(t_node *stack)
{
	int		i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}
