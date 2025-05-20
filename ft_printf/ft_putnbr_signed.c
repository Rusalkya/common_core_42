/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_signed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:38:18 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/12 15:02:36 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnbr_signed(int nbr)
{
	size_t	count;
	long	nb;

	count = 0;
	nb = (long)nbr;
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
	}
	count += ft_putnbr_unsigned((unsigned int)nb, "0123456789");
	return (count);
}
