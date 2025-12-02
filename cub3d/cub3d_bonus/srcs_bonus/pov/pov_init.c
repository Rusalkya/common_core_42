/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:11:57 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:56:28 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_img	*load_pov_image(t_hub *hub, char *path);
void	init_pov_struct(t_hub *hub);

static void	load_pov_empty_sprites(t_hub *hub)
{
	hub->pov->empty1 = load_pov_image(hub, "./textures/pov/pov_empty1.xpm");
	hub->pov->empty2 = load_pov_image(hub, "./textures/pov/pov_empty2.xpm");
}

static void	load_pov_hammer_sprites(t_hub *hub)
{
	hub->pov->hammer1 = load_pov_image(hub, "./textures/pov/pov_hammer1.xpm");
	hub->pov->hammer2 = load_pov_image(hub, "./textures/pov/pov_hammer2.xpm");
}

static void	load_pov_attack_sprites(t_hub *hub)
{
	hub->pov->hammer_hit1 = load_pov_image(hub,
			"./textures/pov/pov_hammer_hit1.xpm");
	hub->pov->hammer_hit2 = load_pov_image(hub,
			"./textures/pov/pov_hammer_hit2.xpm");
	hub->pov->hammer_hit3 = load_pov_image(hub,
			"./textures/pov/pov_hammer_hit3.xpm");
	hub->pov->hammer_pow = load_pov_image(hub,
			"./textures/pov/pov_hammer_hit_pow.xpm");
	hub->pov->hammer_crack = load_pov_image(hub,
			"./textures/pov/pov_hammer_hit_crack.xpm");
	hub->pov->hammer_boom = load_pov_image(hub,
			"./textures/pov/pov_hammer_hit_boom.xpm");
}

void	init_pov(t_hub *hub)
{
	init_pov_struct(hub);
	load_pov_empty_sprites(hub);
	load_pov_hammer_sprites(hub);
	load_pov_attack_sprites(hub);
}
