/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_hole_anim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:50:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 11:10:35 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	swap_pixels(t_img *img, int x, int y)
{
	char			*left_pixel;
	char			*right_pixel;
	unsigned int	temp;

	left_pixel = img->addr + (y * img->line + x * (img->bpp / 8));
	right_pixel = img->addr + (y * img->line + (img->w - 1 - x)
			* (img->bpp / 8));
	temp = *(unsigned int *)left_pixel;
	*(unsigned int *)left_pixel = *(unsigned int *)right_pixel;
	*(unsigned int *)right_pixel = temp;
}

void	flip_image_horizontal(t_img *img)
{
	int	x;
	int	y;

	if (!img || !img->ptr || !img->addr)
		return ;
	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w / 2)
		{
			swap_pixels(img, x, y);
			x++;
		}
		y++;
	}
}

void	update_wall_hole_animation(t_hub *hub)
{
	hub->mlx->wall_hole_counter++;
	if (hub->mlx->wall_hole_counter >= 15)
	{
		hub->mlx->wall_hole_frame = 1 - hub->mlx->wall_hole_frame;
		hub->mlx->wall_hole_counter = 0;
	}
}

t_img	*get_wall_hole_sprite(t_hub *hub)
{
	if (hub->mlx->wall_hole_frame == 0)
		return (hub->mlx->wall_hole1);
	return (hub->mlx->wall_hole2);
}
