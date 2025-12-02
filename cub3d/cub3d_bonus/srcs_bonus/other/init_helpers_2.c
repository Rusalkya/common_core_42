/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 10:41:05 by clfouger          #+#    #+#             */
/*   Updated: 2025/12/02 16:12:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_basic_images(t_hub *hub, int i)
{
	if (i >= 1)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->no->ptr);
	if (i >= 2)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->so->ptr);
	if (i >= 3)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->we->ptr);
	if (i >= 4)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->ea->ptr);
}

static void	free_crack_images(t_hub *hub, int i)
{
	if (i >= 5)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->so_crack->ptr);
	if (i >= 6)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->so_crack2->ptr);
	if (i >= 7)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->so_crack3->ptr);
	if (i >= 8)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->wall_hole1->ptr);
	if (i >= 9)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->wall_hole2->ptr);
}

static void	free_sprite_images(t_hub *hub, int i)
{
	int	j;

	if (i >= 10)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->hammer_sprite->ptr);
	if (i >= 11)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->floor_sprite->ptr);
	if (i >= 12)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->roof_sprite->ptr);
	j = 0;
	while (j < 3 && i >= 13 + j)
	{
		if (hub->mlx->screamers[j] && hub->mlx->screamers[j]->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->mlx->screamers[j]->ptr);
		j++;
	}
}

static void	free_image_structs(t_hub *hub)
{
	int	j;

	free(hub->mlx->no);
	free(hub->mlx->so);
	free(hub->mlx->we);
	free(hub->mlx->ea);
	free(hub->mlx->so_crack);
	free(hub->mlx->so_crack2);
	free(hub->mlx->so_crack3);
	free(hub->mlx->wall_hole1);
	free(hub->mlx->wall_hole2);
	free(hub->mlx->hammer_sprite);
	free(hub->mlx->floor_sprite);
	free(hub->mlx->roof_sprite);
	j = 0;
	while (j < 3)
		free(hub->mlx->screamers[j++]);
}

void	free_image(t_hub *hub, int i)
{
	free_basic_images(hub, i);
	free_crack_images(hub, i);
	free_sprite_images(hub, i);
	free_image_structs(hub);
}
