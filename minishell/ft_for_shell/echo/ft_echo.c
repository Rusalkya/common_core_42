/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:01:34 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:04:47 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

void	ft_echo(t_cmd *echo)
{
	if (echo->option != 'n')
		ft_printf(echo->fd, "%s\n", echo->src[0]);
	else
		ft_printf(echo->fd, echo->src[0]);
}
