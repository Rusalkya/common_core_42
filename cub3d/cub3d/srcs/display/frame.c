/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:08:14 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/21 13:50:51 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	frame(t_hub *hub)
{
	process_movement(hub);
	draw_roof_floor(hub->frame, hub);
	raycasting_wall(hub);
	mlx_put_image_to_window(hub->mlx->mlx, hub->mlx->win, hub->frame->ptr,
		0, 0);
	return ((void)hub, 0);
}
