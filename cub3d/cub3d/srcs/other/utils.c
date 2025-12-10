/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:32:42 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/21 13:54:09 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	get_px(const t_img *frame, int x, int y)
{
	const char	*src;

	if (x < 0 || y < 0 || x >= frame->w || y >= frame->h)
		return (0);
	src = frame->addr + y * frame->line + x * (frame->bpp / 8);
	return (*(const unsigned int *)src);
}

void	put_px(t_img *frame, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= frame->w || y >= frame->h)
		return ;
	dst = frame->addr + y * frame->line + x * (frame->bpp / 8);
	*(unsigned int *)dst = color;
}

void	draw_roof_floor(t_img *frame, t_hub *hub)
{
	int		x;
	int		y;
	int		mid;

	mid = frame->h / 2;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (y < mid)
				put_px(frame, x, y, hub->mlx->ceil_color);
			else
				put_px(frame, x, y, hub->mlx->floor_color);
			x++;
		}
		y++;
	}
}

void	init_tex_coords(t_ray *ray, t_img *tex)
{
	ray->tex_x = (int)(ray->wall_x * (double)tex->w);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = tex->w - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = tex->w - ray->tex_x - 1;
	ray->tex_step = (double)tex->h / (double)ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2)
		* ray->tex_step;
}
