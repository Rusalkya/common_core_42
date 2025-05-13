/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:43:48 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/13 10:46:08 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putaddress(void *ptr)
{
	unsigned long long	address;
	size_t				len;

	if (!ptr)
		return (ft_putstr("(nil)"));
	address = (unsigned long)ptr;
	len = ft_putstr("0x");
	len += ft_putnbr_unsigned(address, "0123456789abcdef");
	return (len);
}
