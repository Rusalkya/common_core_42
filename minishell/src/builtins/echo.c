/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:01:34 by cade-jes          #+#    #+#             */
/*   Updated: 2025/09/11 12:07:58 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_cmd *echo)
{
	if (echo->option != 'n')
		ft_printf(echo->fd, "%s\n", echo->src[0]);
	else
		ft_printf(echo->fd, echo->src[0]);
}
