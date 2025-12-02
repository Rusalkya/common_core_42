/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_click.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:54:55 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:56:58 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mouse_click(int button, int x, int y, t_hub *hub)
{
	(void)x;
	(void)y;
	if (button == 1)
		start_hammer_attack(hub);
	return (0);
}
