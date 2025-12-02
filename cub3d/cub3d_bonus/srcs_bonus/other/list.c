/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:35:52 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/27 12:40:13 by clfouger         ###   ########.fr       */
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
	key->ctrl = 0;
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
	init_hub_timer_values(hub);
	return (hub);
}
