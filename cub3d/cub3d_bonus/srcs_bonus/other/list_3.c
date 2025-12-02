/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:50:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 12:40:13 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	init_ray_values(t_ray *ray)
{
	ray->camera_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side = 0;
	ray->perp_wall_dist = 0;
	ray->line_height = 0;
	ray->draw_end = 0;
	ray->draw_start = 0;
	ray->wall_x = 0;
	ray->tex_x = 0;
	ray->tex_step = 0;
	ray->tex_pos = 0;
}

t_ray	*creat_ray(t_hub *hub)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (msg_error("ray", "malloc", strerror(errno)), ft_exit(hub, 1),
			NULL);
	init_ray_values(ray);
	return (ray);
}

void	init_hub_timer_values(t_hub *hub)
{
	hub->door_broken = 0;
	hub->timer_active = 0;
	hub->timer_seconds = 100;
	hub->screamer_counter = 0;
	hub->show_screamer = 0;
	hub->screamer_index = 0;
	hub->screamer_display_time = 0;
	hub->ambiance_started = 0;
	hub->total_screamers = 0;
	hub->screamer_sound_played = 0;
	hub->final_screamer_active = 0;
	hub->final_screamer_frame = 0;
	hub->final_screamer_counter = 0;
	hub->fade_to_black_progress = 0;
	hub->is_moving = 0;
	hub->has_hammer = 0;
	hub->footstep_pid = -1;
	hub->ambiance_pid = -1;
	hub->music_pid = -1;
	hub->end_sound_pid = -1;
}
