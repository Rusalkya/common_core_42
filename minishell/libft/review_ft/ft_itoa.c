/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:05:37 by cade-jes          #+#    #+#             */
/*   Updated: 2025/05/28 11:21:31 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	len_dst(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	long long	nb;
	char		*dst;

	nb = n;
	i = len_dst(nb);
	dst = malloc(sizeof(char) * i + 1);
	if (!dst)
		return (NULL);
	dst[i] = 0;
	if (nb == 0)
		dst[0] = '0';
	else if (nb < 0)
	{
		dst[0] = '-';
		nb *= -1;
	}
	while (nb)
	{
		i--;
		dst[i] = nb % 10 + '0';
		nb /= 10;
	}
	return (dst);
}
