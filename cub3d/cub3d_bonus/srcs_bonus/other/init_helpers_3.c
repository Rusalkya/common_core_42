/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:23:05 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 17:54:41 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_wall(t_mlx *mlx, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(mlx->mlx, path, &img->w, &img->h);
	if (!img->ptr)
		return (msg_error("mlx_xpm_file_to_image", path, NULL), 1);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line,
			&img->endian);
	return (0);
}

void	load_basic_walls(t_hub *hub)
{
	if (!hub->mlx->no_path || !hub->mlx->so_path
		|| !hub->mlx->we_path || !hub->mlx->ea_path)
	{
		msg_error("Missing wall texture path", NULL, NULL);
		return (free_image(hub, 0), ft_exit(hub, 1));
	}
	hub->mlx->ea = creat_img(hub);
	hub->mlx->no = creat_img(hub);
	hub->mlx->we = creat_img(hub);
	hub->mlx->so = creat_img(hub);
	if (load_wall(hub->mlx, hub->mlx->no, hub->mlx->no_path))
		return (free_image(hub, 0), ft_exit(hub, 1));
	if (load_wall(hub->mlx, hub->mlx->so, hub->mlx->so_path))
		return (free_image(hub, 1), ft_exit(hub, 1));
	if (load_wall(hub->mlx, hub->mlx->we, hub->mlx->we_path))
		return (free_image(hub, 2), ft_exit(hub, 1));
	if (load_wall(hub->mlx, hub->mlx->ea, hub->mlx->ea_path))
		return (free_image(hub, 3), ft_exit(hub, 1));
}

void	load_crack_walls(t_hub *hub)
{
	if (load_wall(hub->mlx, hub->mlx->so_crack, "textures/wallSO_crack1.xpm"))
		return (free_image(hub, 4), ft_exit(hub, 1));
	if (load_wall(hub->mlx, hub->mlx->so_crack2, "textures/wallSO_crack2.xpm"))
		return (free_image(hub, 5), ft_exit(hub, 1));
	if (load_wall(hub->mlx, hub->mlx->so_crack3, "textures/wallSO_crack3.xpm"))
		return (free_image(hub, 6), ft_exit(hub, 1));
}

void	load_hole_walls(t_hub *hub)
{
	if (load_wall(hub->mlx, hub->mlx->wall_hole1, "textures/wall_hole1.xpm"))
		return (free_image(hub, 7), ft_exit(hub, 1));
	if (load_wall(hub->mlx, hub->mlx->wall_hole2, "textures/wall_hole2.xpm"))
		return (free_image(hub, 8), ft_exit(hub, 1));
}

void	load_sprite_textures(t_hub *hub)
{
	if (load_wall(hub->mlx, hub->mlx->hammer_sprite, "textures/hammer.xpm"))
		return (free_image(hub, 9), ft_exit(hub, 1));
}
