/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:43:14 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/24 12:55:47 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_mini(t_mini *mini, t_2v a, t_2v b)
{
	mini->dx = abs(b.x - a.x);
	mini->dy = -abs(b.y - a.y);
	if (a.x < b.x)
		mini->sx = 1;
	else
		mini->sx = -1;
	if (a.y < b.y)
		mini->sy = 1;
	else
		mini->sy = -1;
	mini->err = mini->dx + mini->dy;
}

static void	draw_line_minimap(t_img *frame, t_2v b)
{
	t_2v	a;
	t_mini	mini;

	a.x = MN_CX;
	a.y = MN_CY;
	init_mini(&mini, a, b);
	while (1)
	{
		if (verif_draw_minimap(a.x, a.y))
			put_px(frame, a.x, a.y, FOV);
		if (a.x == b.x && a.y == b.y)
			break ;
		mini.e2 = 2 * mini.err;
		if (mini.e2 >= mini.dy)
		{
			mini.err += mini.dy;
			a.x += mini.sx;
		}
		if (mini.e2 <= mini.dx)
		{
			mini.err += mini.dx;
			a.y += mini.sy;
		}
	}
}

void	draw_rays_on_minimap(t_hub *hub, t_ray *ray)
{
	int		i;
	t_2v	hit_px;
	double	wall_dist;
	double	hit_x;
	double	hit_y;

	i = 0;
	while (i < WIN_W)
	{
		init_dda(hub, ray, i);
		dda(hub, ray);
		if (ray->side == 0)
			wall_dist = (ray->map_x - hub->player->posx
					+ (1.0 - ray->step_x) / 2.0) / ray->ray_dir_x;
		else
			wall_dist = (ray->map_y - hub->player->posy
					+ (1.0 - ray->step_y) / 2.0) / ray->ray_dir_y;
		hit_x = hub->player->posx + ray->ray_dir_x * wall_dist;
		hit_y = hub->player->posy + ray->ray_dir_y * wall_dist;
		hit_px.x = MN_CX + (int)((hit_x - hub->player->posx) * MINIMAP_SCALE);
		hit_px.y = MN_CY + (int)((hit_y - hub->player->posy) * MINIMAP_SCALE);
		draw_line_minimap(hub->frame, hit_px);
		i++;
	}
}
