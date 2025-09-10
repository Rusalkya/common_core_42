/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:33:57 by cade-jes          #+#    #+#             */
/*   Updated: 2025/05/28 11:22:20 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *src)
{
	int	i;
	int	s;
	int	result;

	i = 0;
	while ((src[i] >= 9 && src[i] <= 13) || src[i] == ' ')
		i++;
	if (src[i] == '-')
		s = 1;
	if (src[i] == '-' || src[i] == '+')
		i++;
	result = 0;
	while (src[i] >= '0' && src[i] <= '9')
	{
		result = result * 10 + (src[i] - '0');
		i++;
	}
	if (s == 1)
		return (result * -1);
	return (result);
}
