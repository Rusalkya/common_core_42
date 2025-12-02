/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:29:58 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 10:23:05 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	compute_perp_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist < 0.001)
		ray->perp_wall_dist = 0.001;
}

void	compute_line_limits(t_ray *ray)
{
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

void	compute_wall_x(t_hub *hub, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = hub->player->posy
			+ ray->ray_dir_y * ray->perp_wall_dist;
	else
		ray->wall_x = hub->player->posx
			+ ray->ray_dir_x * ray->perp_wall_dist;
	ray->wall_x -= floor(ray->wall_x);
}
