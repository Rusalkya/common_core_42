/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_pf.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:15:35 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/24 09:34:06 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putnbr_unsigned_pf(unsigned long long nbr, char *base)
{
	size_t	base_len;
	size_t	count;

	base_len = 0;
	count = 0;
	while (base[base_len])
		base_len++;
	if (nbr >= base_len)
		count += ft_putnbr_unsigned_pf(nbr / base_len, base);
	count += ft_putchar_pf(base[nbr % base_len]);
	return (count);
}
