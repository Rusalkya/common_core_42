/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 04:29:43 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/24 11:41:43 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	dda(t_hub *hub, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (hub->map[ray->map_y][ray->map_x] == '1'
			|| hub->map[ray->map_y][ray->map_x] == '2'
			|| hub->map[ray->map_y][ray->map_x] == '3'
			|| hub->map[ray->map_y][ray->map_x] == '4'
			|| hub->map[ray->map_y][ray->map_x] == '5')
			hit = 1;
	}
}

static void	init_dda_2(t_hub *hub, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (hub->player->posx - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - hub->player->posx)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (hub->player->posy - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - hub->player->posy)
			* ray->delta_dist_y;
	}
}

void	init_dda(t_hub *hub, t_ray *ray, int i)
{
	ray->camera_x = 2.0 * i / (double)WIN_W - 1.0;
	ray->ray_dir_x = hub->player->dirx + hub->player->planex * ray->camera_x;
	ray->ray_dir_y = hub->player->diry + hub->player->planey * ray->camera_x;
	ray->map_x = (int)hub->player->posx;
	ray->map_y = (int)hub->player->posy;
	if (ray->ray_dir_x == 0.0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	init_dda_2(hub, ray);
}

void	raycasting_wall(t_hub *hub)
{
	int		i;

	i = 0;
	while (i < WIN_W)
	{
		init_dda(hub, hub->ray, i);
		dda(hub, hub->ray);
		draw_wall(hub, hub->ray, i);
		i++;
	}
}
