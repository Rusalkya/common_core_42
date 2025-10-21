/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:13:44 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/08 13:17:06 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	len_malloc(unsigned long n)
{
	int	i;

	i = 2;
	if (n == 0)
		i++;
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static void	ft_putnbr_hexa(unsigned long nbr, char *str)
{
	unsigned long	i;
	unsigned long	n;

	i = len_malloc(nbr) - 1;
	str[0] = '0';
	str[1] = 'x';
	str[i + 1] = '\0';
	if (nbr == 0)
		str[2] = '0';
	while (nbr)
	{
		n = nbr % 16;
		if (n > 9)
			str[i] = (n - 10) + 'a';
		else
			str[i] = n + '0';
		nbr /= 16;
		i--;
	}
}

void	ftputadress(const char *s, va_list args, t_lst *list)
{
	char			*str;
	unsigned long	nbr;

	nbr = (unsigned long)va_arg(args, void *);
	if (nbr == 0)
	{
		ft_putstr_fd("(nil)", list->fd);
		*list->back += 5;
		hub(&s[1], args, list);
		return ;
	}
	str = malloc(len_malloc(nbr) + 1);
	if (!str)
		return ;
	ft_putnbr_hexa(nbr, str);
	ft_putstr_fd(str, list->fd);
	*list->back += ft_strlen(str);
	free (str);
	hub(&s[1], args, list);
}
