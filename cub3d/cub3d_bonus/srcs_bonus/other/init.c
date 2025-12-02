/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:06:20 by cade-jes          #+#    #+#             */
/*   Updated: 2025/12/02 16:12:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	load_screamers(t_hub *hub)
{
	int		i;
	char	path[50];

	i = -1;
	while (++i < 3)
	{
		snprintf(path, sizeof(path),
			"textures/screamers/screamer%d.xpm", i + 1);
		if (load_wall(hub->mlx, hub->mlx->screamers[i], path))
			return (free_image(hub, 18 + i), ft_exit(hub, 1));
	}
}

static void	init_wall(t_hub *hub)
{
	load_basic_walls(hub);
	load_crack_walls(hub);
	load_hole_walls(hub);
	load_sprite_textures(hub);
	load_screamers(hub);
	flip_image_horizontal(hub->mlx->wall_hole1);
	flip_image_horizontal(hub->mlx->wall_hole2);
}

void	init(t_hub *hub, t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (msg_error("mlx_init", NULL, NULL), ft_exit(hub, 1));
	mlx->win = mlx_new_window(mlx->mlx, hub->frame->w, hub->frame->h, "cub3d");
	if (!mlx->win)
		return (msg_error("mlx_new_window", NULL, NULL), ft_exit(hub, 1));
	hub->frame->ptr = mlx_new_image(mlx->mlx, hub->frame->w, hub->frame->h);
	if (!hub->frame->ptr)
		return (msg_error("mlx_new_image", NULL, NULL), ft_exit(hub, 1));
	hub->frame->addr = mlx_get_data_addr(hub->frame->ptr, &hub->frame->bpp,
			&hub->frame->line, &hub->frame->endian);
	init_wall(hub);
	init_pov(hub);
}
