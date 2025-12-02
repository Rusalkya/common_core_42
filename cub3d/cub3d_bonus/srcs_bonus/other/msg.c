/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:21:32 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/05 14:40:32 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	msg_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(BOLD RED "Error" RST RED, STDERR_FILENO);
	if (s1)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s1, STDERR_FILENO);
	}
	if (s2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	if (s3)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s3, STDERR_FILENO);
	}
	ft_putstr_fd(RST "\n", STDERR_FILENO);
}
