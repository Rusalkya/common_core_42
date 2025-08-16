/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_signed_pf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:15:22 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/24 09:34:03 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putnbr_signed_pf(int nbr)
{
	size_t	count;
	long	nb;

	count = 0;
	nb = (long)nbr;
	if (nb < 0)
	{
		count += ft_putchar_pf('-');
		nb = -nb;
	}
	count += ft_putnbr_unsigned_pf((unsigned int)nb, "0123456789");
	return (count);
}
