/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:06:20 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/27 16:15:50 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_image(t_hub *hub, int i)
{
	if (i >= 1)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->no->ptr);
	if (i >= 2)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->so->ptr);
	if (i >= 3)
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->we->ptr);
	free(hub->mlx->no);
	free(hub->mlx->so);
	free(hub->mlx->we);
	free(hub->mlx->ea);
	hub->mlx->ea = NULL;
	hub->mlx->we = NULL;
	hub->mlx->so = NULL;
	hub->mlx->no = NULL;
}

static int	load_wall(t_mlx *mlx, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(mlx->mlx, path, &img->w, &img->h);
	if (!img->ptr)
		return (msg_error("mlx_xpm_file_to_image", path, NULL), 1);
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line,
			&img->endian);
	return (0);
}

static void	init_wall(t_hub *hub)
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
}
