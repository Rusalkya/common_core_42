/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:38:30 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/12 15:23:08 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putnbr_unsigned(unsigned long long nbr, char *base)
{
	size_t	base_len;
	size_t	count;

	base_len = 0;
	count = 0;
	while (base[base_len])
		base_len++;
	if (nbr >= base_len)
		count += ft_putnbr_unsigned(nbr / base_len, base);
	count += ft_putchar(base[nbr % base_len]);
	return (count);
}
/*
int main ()
{
	int n = 42;
	ft_putnbr_base(n, "0123456789abcdef");
	write (1, "\n", 1);
	ft_putnbr_base(n, "01");
	write (1, "\n", 1);
	ft_putnbr_base(n, "0123456789");
	write (1, "\n", 1);
	ft_putnbr_base(n, "01234567");
}
*/