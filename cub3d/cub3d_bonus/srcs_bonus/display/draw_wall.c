/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:11:22 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/25 12:20:47 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	compute_perp_dist(t_ray *ray);
void	compute_line_limits(t_ray *ray);
void	compute_wall_x(t_hub *hub, t_ray *ray);

static t_img	*select_wall_tex(t_hub *hub, t_ray *ray)
{
	char	cell;

	cell = hub->map[ray->map_y][ray->map_x];
	if (cell == '2')
		return (hub->mlx->so_crack);
	if (cell == '3')
		return (hub->mlx->so_crack2);
	if (cell == '4')
		return (hub->mlx->so_crack3);
	if (cell == '5')
		return (get_wall_hole_sprite(hub));
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

static void	render_wall_column(t_hub *hub, t_ray *ray, t_img *tex, int x)
{
	int	y;
	int	tex_y;
	int	color;

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
		if ((color & 0x00FFFFFF) != 0x00FF00FF)
			put_px(hub->frame, x, y, color);
		y++;
	}
}

void	draw_wall(t_hub *hub, t_ray *ray, int x)
{
	t_img	*tex;

	compute_perp_dist(ray);
	compute_line_limits(ray);
	compute_wall_x(hub, ray);
	tex = select_wall_tex(hub, ray);
	init_tex_coords(ray, tex);
	render_wall_column(hub, ray, tex, x);
}
