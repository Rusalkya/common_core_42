/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:35:52 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/27 12:56:24 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_key	*creat_key(t_hub *hub)
{
	t_key	*key;

	key = malloc(sizeof(t_key));
	if (!key)
		return (msg_error("key", "malloc", strerror(errno)), ft_exit(hub, 1),
			NULL);
	key->w = 0;
	key->a = 0;
	key->s = 0;
	key->d = 0;
	key->r = 0;
	key->l = 0;
	return (key);
}

static t_img	*creat_frame(t_hub *hub)
{
	t_img	*frame;

	frame = malloc(sizeof(t_img));
	if (!frame)
		return (msg_error("frame", "malloc", strerror(errno)), ft_exit(hub, 1),
			NULL);
	frame->ptr = NULL;
	frame->addr = NULL;
	frame->w = WIN_W;
	frame->h = WIN_H;
	return (frame);
}

static t_player	*creat_player(t_hub *hub)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (msg_error("player", "malloc", strerror(errno)), ft_exit(hub, 1),
			NULL);
	player->posx = 5.0;
	player->posy = 5.0;
	player->dirx = -1.0;
	player->diry = 0.0;
	player->planex = 0.0;
	player->planey = 0.0;
	return (player);
}

static t_ray	*creat_ray(t_hub *hub)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (msg_error("ray", "malloc", strerror(errno)), ft_exit(hub, 1),
			NULL);
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
	return (ray);
}

t_hub	*creat_hub(void)
{
	t_hub	*hub;

	hub = malloc(sizeof(t_hub));
	if (!hub)
		return (msg_error("hub", "malloc", strerror(errno)), ft_exit(hub, 1),
			NULL);
	hub->mlx = creat_mlx(hub);
	hub->map = NULL;
	hub->key = creat_key(hub);
	hub->frame = creat_frame(hub);
	hub->player = creat_player(hub);
	hub->ray = creat_ray(hub);
	return (hub);
}
