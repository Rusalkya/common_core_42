/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hammer_world_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:50:57 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 14:14:09 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_hammer_draw(t_hammer_draw *d, t_hub *hub, t_hammer *hammer)
{
	d->dx = hammer->x + 0.5 - hub->player->posx;
	d->dy = hammer->y + 0.5 - hub->player->posy;
	d->distance = sqrt(d->dx * d->dx + d->dy * d->dy);
}

void	calc_hammer_screen_pos(t_hammer_draw *d, t_hub *hub)
{
	d->angle = atan2(d->dy, d->dx);
	d->relative_angle = d->angle - atan2(hub->player->diry, hub->player->dirx);
	while (d->relative_angle > M_PI)
		d->relative_angle -= 2 * M_PI;
	while (d->relative_angle < -M_PI)
		d->relative_angle += 2 * M_PI;
	d->screen_x = (int)((WIN_W / 2) * (1 + tan(d->relative_angle)
				/ tan(M_PI / 3)));
	d->sprite_height = (int)(WIN_H / d->distance) / 3;
}

void	get_tex_coord(int *tex_x, int stripe, t_hub *hub, int sh)
{
	*tex_x = stripe * hub->mlx->hammer_sprite->w / sh;
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= hub->mlx->hammer_sprite->w)
		*tex_x = hub->mlx->hammer_sprite->w - 1;
}
