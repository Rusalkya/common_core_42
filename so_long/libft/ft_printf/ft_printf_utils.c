/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:39:01 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/24 09:33:57 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putchar_pf(char c)
{
	return (write(1, &c, 1));
}

size_t	ft_strlen_pf(const char *src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

size_t	ft_putstr_pf(char *s)
{
	size_t	len;

	if (!s)
		return (write(1, "(null)", 6));
	len = ft_strlen_pf(s);
	write(1, s, len);
	return (len);
}

size_t	ft_putaddress_pf(void *ptr)
{
	unsigned long long	address;
	size_t				len;

	if (!ptr)
		return (ft_putstr_pf("(nil)"));
	address = (unsigned long)ptr;
	len = ft_putstr_pf("0x");
	len += ft_putnbr_unsigned_pf(address, "0123456789abcdef");
	return (len);
}
