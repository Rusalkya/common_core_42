/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:45:17 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 13:05:18 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

typedef struct s_pov_draw
{
	unsigned int	color;
	int				screen_x;
	int				screen_y;
	int				offset_x;
	int				offset_y;
}					t_pov_draw;

static void	draw_scaled_pixel(t_hub *hub, t_pov_draw *d)
{
	int	i;
	int	j;

	i = 0;
	while (i < 15)
	{
		j = 0;
		while (j < 15)
		{
			if (d->screen_x + i >= 0 && d->screen_x + i < WIN_W
				&& d->screen_y + j >= 0 && d->screen_y + j < WIN_H)
				put_px(hub->frame, d->screen_x + i, d->screen_y + j, d->color);
			j++;
		}
		i++;
	}
}

static void	draw_pov_pixel_scaled(t_hub *hub, t_img *sprite, int sx, int sy)
{
	t_pov_draw	d;

	d.offset_x = (WIN_W - (int)(sprite->w * 15)) / 2;
	d.offset_y = WIN_H - (int)(sprite->h * 15);
	d.color = get_px(sprite, sx, sy);
	if (is_transparent(d.color))
		return ;
	d.screen_x = d.offset_x + (int)(sx * 15);
	d.screen_y = d.offset_y + (int)(sy * 15);
	draw_scaled_pixel(hub, &d);
}

static void	draw_sprite_pixels(t_hub *hub, t_img *sprite)
{
	int	x;
	int	y;

	y = 0;
	while (y < sprite->h)
	{
		x = 0;
		while (x < sprite->w)
		{
			draw_pov_pixel_scaled(hub, sprite, x, y);
			x++;
		}
		y++;
	}
}

void	render_pov(t_hub *hub)
{
	t_img	*sprite;

	if (!hub->pov)
		return ;
	sprite = get_current_pov_sprite(hub);
	if (!sprite)
		return ;
	draw_sprite_pixels(hub, sprite);
}
