/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:32:41 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/25 17:59:01 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	check_duplicates(t_node *stack)
{
	t_node	*current;

	while (stack)
	{
		current = stack->next;
		while (current)
		{
			if (current->value == stack->value)
				return (1);
			current = current->next;
		}
		stack = stack->next;
	}
	return (0);
}

int	parsing_is_valid(char **args, t_node *a)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!is_valid_int(args[i]))
			return (0);
		i++;
	}
	if (check_duplicates(a) == 1)
		return (0);
	return (1);
}
