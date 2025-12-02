/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:08:14 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/27 12:40:13 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	frame(t_hub *hub)
{
	process_movement(hub);
	check_hammer_collect(hub);
	update_timer(hub);
	update_pov_animation(hub);
	update_hammer_attack(hub);
	update_wall_hole_animation(hub);
	update_final_screamer(hub);
	draw_roof_floor(hub);
	raycasting_wall(hub);
	render_red_filter(hub);
	render_hammers_in_world(hub);
	minimap(hub);
	render_hammers(hub);
	render_pov(hub);
	render_screamer(hub);
	render_final_fade(hub);
	render_timer_display(hub);
	mlx_put_image_to_window(hub->mlx->mlx, hub->mlx->win, hub->frame->ptr,
		0, 0);
	return ((void)hub, 0);
}
