/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:23:05 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 11:10:35 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_texture(t_hub *hub, t_img *img)
{
	if (img && hub->mlx->mlx)
	{
		if (img->ptr)
			mlx_destroy_image(hub->mlx->mlx, img->ptr);
		free(img);
	}
}

void	free_basic_textures(t_hub *hub)
{
	free_texture(hub, hub->mlx->ea);
	free_texture(hub, hub->mlx->we);
	free_texture(hub, hub->mlx->no);
	free_texture(hub, hub->mlx->so);
}

void	free_crack_textures(t_hub *hub)
{
	free_texture(hub, hub->mlx->so_crack);
	free_texture(hub, hub->mlx->so_crack2);
	free_texture(hub, hub->mlx->so_crack3);
}

void	free_hole_textures(t_hub *hub)
{
	free_texture(hub, hub->mlx->wall_hole1);
	free_texture(hub, hub->mlx->wall_hole2);
}

void	free_sprite_textures(t_hub *hub)
{
	free_texture(hub, hub->mlx->hammer_sprite);
	free_texture(hub, hub->mlx->floor_sprite);
	free_texture(hub, hub->mlx->roof_sprite);
}
