/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:20:44 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/13 10:42:57 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
size_t	ft_putstr(char *s)
{
	if (!s)
		return (write (1, "(null)", 6));
	return (write (1, s, ft_strlen(s)));
}
	*/

size_t	ft_putstr(char *s)
{
	size_t	len;

	if (!s)
		return (write(1, "(null)", 6));
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}
