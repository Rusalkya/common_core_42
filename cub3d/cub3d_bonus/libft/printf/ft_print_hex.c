/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:37:23 by carlos            #+#    #+#             */
/*   Updated: 2025/08/08 13:16:05 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	len_hexa(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static void	ft_putnbr_hexa_2(unsigned int nbr, char *str, char format)
{
	char	*hex;
	int		i;

	if (format == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	i = len_hexa(nbr) - 1;
	str[len_hexa(nbr)] = '\0';
	if (nbr == 0)
	{
		str[0] = '0';
		return ;
	}
	while (nbr)
	{
		str[i] = hex[nbr % 16];
		nbr /= 16;
		i--;
	}
}

void	ftprinthexa(const char *s, va_list args, t_lst *list)
{
	char			*str;
	unsigned int	nbr;
	int				len;

	nbr = va_arg(args, unsigned int);
	len = len_hexa(nbr);
	str = malloc(len + 1);
	if (!str)
		return ;
	ft_putnbr_hexa_2(nbr, str, *s);
	ft_putstr_fd(str, list->fd);
	*list->back += ft_strlen(str);
	free(str);
	hub(&s[1], args, list);
}
