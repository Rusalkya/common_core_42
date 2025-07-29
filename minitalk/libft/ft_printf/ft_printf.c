/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:05:18 by clfouger          #+#    #+#             */
/*   Updated: 2025/06/24 09:34:01 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	convert_format(char type, va_list args)
{
	if (type == 'c')
		return (ft_putchar_pf(va_arg(args, int)));
	if (type == 's')
		return (ft_putstr_pf(va_arg(args, char *)));
	else if (type == 'd' || type == 'i')
		return (ft_putnbr_signed_pf(va_arg(args, int)));
	else if (type == 'u')
		return (ft_putnbr_unsigned_pf(va_arg(args, unsigned int),
				"0123456789"));
	else if (type == 'x')
		return (ft_putnbr_unsigned_pf(va_arg(args, unsigned int),
				"0123456789abcdef"));
	else if (type == 'X')
		return (ft_putnbr_unsigned_pf(va_arg(args, unsigned int),
				"0123456789ABCDEF"));
	else if (type == 'p')
		return (ft_putaddress_pf(va_arg(args, void *)));
	else if (type == '%')
		return (ft_putchar_pf('%'));
	return (0);
}

int	valid_type(char type)
{
	if ((type == 'c') || (type == 's') || (type == 'i') || (type == 'd')
		|| (type == 'u') || (type == 'x') || (type == 'X') || (type == 'p')
		|| (type == '%'))
		return (1);
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if ((format[i] == '%') && (valid_type(format[i + 1])))
		{
			count += convert_format(format[i + 1], args);
			i += 2;
		}
		else
		{
			write(1, &format[i], 1);
			i++;
			count++;
		}
	}
	va_end(args);
	return (count);
}
