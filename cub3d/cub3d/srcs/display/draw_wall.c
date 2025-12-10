/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:11:22 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/21 10:51:40 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	compute_perp_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist < 0.001)
		ray->perp_wall_dist = 0.001;
}

static void	compute_line_limits(t_ray *ray)
{
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

static t_img	*select_wall_tex(t_hub *hub, t_ray *ray)
{
	char	cell;

	cell = hub->map[ray->map_y][ray->map_x];
	if (cell == '1')
	{
		if (ray->side == 0 && ray->ray_dir_x > 0)
			return (hub->mlx->ea);
		if (ray->side == 0 && ray->ray_dir_x < 0)
			return (hub->mlx->we);
		if (ray->side == 1 && ray->ray_dir_y > 0)
			return (hub->mlx->so);
		return (hub->mlx->no);
	}
	return (hub->mlx->no);
}

static void	compute_wall_x(t_hub *hub, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = hub->player->posy
			+ ray->ray_dir_y * ray->perp_wall_dist;
	else
		ray->wall_x = hub->player->posx
			+ ray->ray_dir_x * ray->perp_wall_dist;
	ray->wall_x -= floor(ray->wall_x);
}

void	draw_wall(t_hub *hub, t_ray *ray, int x)
{
	t_img	*tex;
	int		y;
	int		tex_y;
	int		color;

	compute_perp_dist(ray);
	compute_line_limits(ray);
	compute_wall_x(hub, ray);
	tex = select_wall_tex(hub, ray);
	init_tex_coords(ray, tex);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)ray->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->h)
			tex_y = tex->h - 1;
		ray->tex_pos += ray->tex_step;
		color = get_px(tex, ray->tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_px(hub->frame, x, y, color);
		y++;
	}
}
