/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:48:19 by cade-jes          #+#    #+#             */
/*   Updated: 2025/12/02 16:12:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*creat_img(t_hub *hub)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (msg_error("img", "malloc", strerror(errno)), ft_exit(hub, 1),
			NULL);
	img->ptr = NULL;
	img->addr = NULL;
	img->w = 128;
	img->h = 128;
	return (img);
}

static void	init_mlx_textures(t_mlx *mlx, t_hub *hub)
{
	mlx->ea = NULL;
	mlx->no = NULL;
	mlx->we = NULL;
	mlx->so = NULL;
	mlx->so_crack = creat_img(hub);
	mlx->so_crack2 = creat_img(hub);
	mlx->so_crack3 = creat_img(hub);
	mlx->wall_hole1 = creat_img(hub);
	mlx->wall_hole2 = creat_img(hub);
	mlx->hammer_sprite = creat_img(hub);
	mlx->floor_sprite = creat_img(hub);
	mlx->roof_sprite = creat_img(hub);
}

static void	init_mlx_values(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < 3)
		mlx->screamers[i++] = NULL;
	mlx->wall_hole_frame = 0;
	mlx->wall_hole_counter = 0;
	mlx->no_path = NULL;
	mlx->so_path = NULL;
	mlx->we_path = NULL;
	mlx->ea_path = NULL;
	mlx->floor_color = 0;
	mlx->ceil_color = 0;
}

t_mlx	*creat_mlx(t_hub *hub)
{
	t_mlx	*mlx;
	int		i;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (msg_error("mlx", "malloc", strerror(errno)), ft_exit(hub, 1),
			NULL);
	mlx->mlx = NULL;
	mlx->win = NULL;
	init_mlx_values(mlx);
	init_mlx_textures(mlx, hub);
	i = 0;
	while (i < 3)
		mlx->screamers[i++] = creat_img(hub);
	return (mlx);
}
