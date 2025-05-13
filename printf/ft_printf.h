/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:09:55 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/12 15:15:02 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

int			ft_printf(const char *format, ...);
size_t		ft_putchar(char c);
size_t		ft_putstr(char *s);
size_t		ft_putnbr_signed(int nbr);
size_t		ft_putnbr_unsigned(unsigned long long nbr, char *base);
size_t		ft_putaddress(void *ptr);
size_t		ft_strlen(const char *src);

#endif
