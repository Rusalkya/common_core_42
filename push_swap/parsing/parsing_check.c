/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:40:03 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/27 15:41:04 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	int_limit_ok(const char *str, int i, int sign)
{
	long long	nb;

	nb = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		nb = nb * 10 + (str[i] - '0');
		if ((sign == 1 && nb > INT_MAX) || (sign == -1 && (-nb) < INT_MIN))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_int(const char *str)
{
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '-')
	{
		if (str[i + 1] == '\0')
			return (0);
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		return (0);
	return (int_limit_ok(str, i, sign));
}

int	ft_atoi_safer(const char *str)
{
	long long	nb;
	int			sign;
	int			i;

	nb = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(nb * sign));
}

int	is_sorted(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
