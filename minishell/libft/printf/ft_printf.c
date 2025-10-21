/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:29:05 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/08 13:15:53 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	percent_arg(const char *s, va_list args, t_lst *list)
{
	if (s[0] == 'c')
		ftputchar(s, args, list);
	else if (s[0] == 's')
		ftputstr(s, args, list);
	else if (s[0] == 'p')
		ftputadress(s, args, list);
	else if (s[0] == 'd' || s[0] == 'i')
		ftputnbr(s, args, list);
	else if (s[0] == 'u')
		ftputnbr_u(s, args, list);
	else if (s[0] == 'x' || s[0] == 'X')
		ftprinthexa(s, args, list);
	else if (s[0] == '%')
	{
		write(list->fd, "%%", 1);
		*list->back += 1;
		hub(&s[1], args, list);
	}
}

void	hub(const char *s, va_list args, t_lst *list)
{
	int	i;
	int	x;

	i = 0;
	x = *list->back;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			*list->back = x;
			percent_arg(&s[i], args, list);
			return ;
		}
		write(list->fd, &s[i], 1);
		x++;
		i++;
	}
	*list->back = x;
}

int	ft_printf(int fd, const char *s, ...)
{
	int		value;
	va_list	args;
	t_lst	*list;

	value = 0;
	list = malloc(sizeof(t_lst));
	if (!list)
		return (0);
	list->fd = fd;
	list->back = &value;
	va_start(args, s);
	hub(s, args, list);
	va_end(args);
	free (list);
	return (value);
}
