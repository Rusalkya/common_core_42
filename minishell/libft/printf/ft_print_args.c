/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:13:55 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/08 14:52:21 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_putnbr_unsigned(unsigned int n, t_lst *list)
{
	if (n > 9)
	{
		ft_putnbr_unsigned(n / 10, list);
		ft_putnbr_unsigned(n % 10, list);
	}
	else
		ft_putchar_fd(n + '0', list->fd);
}

void	ftputnbr_u(const char *s, va_list args, t_lst *list)
{
	int				i;
	unsigned int	nbr;

	i = 0;
	nbr = va_arg(args, unsigned int);
	ft_putnbr_unsigned(nbr, list);
	if (nbr == 0)
		i++;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	*list->back += i;
	hub(&s[1], args, list);
}

void	ftputnbr(const char *s, va_list args, t_lst *list)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = va_arg(args, int);
	ft_putnbr_fd(nbr, 1);
	if (nbr == 0 || nbr < 0)
		i++;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	*list->back += i;
	hub(&s[1], args, list);
}

void	ftputstr(const char *s, va_list args, t_lst *list)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
	{
		*list->back += 6;
		ft_putstr_fd("(null)", 1);
		hub(&s[1], args, list);
		return ;
	}
	ft_putstr_fd(str, list->fd);
	*list->back += ft_strlen(str);
	hub(&s[1], args, list);
}

void	ftputchar(const char *s, va_list args, t_lst *list)
{
	ft_putchar_fd((char)va_arg(args, int), list->fd);
	*list->back += 1;
	hub(&s[1], args, list);
}
