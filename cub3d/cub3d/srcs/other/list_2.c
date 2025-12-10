/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:48:19 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/27 16:20:59 by cade-jes         ###   ########.fr       */
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

t_mlx	*creat_mlx(t_hub *hub)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (msg_error("mlx", "malloc", strerror(errno)), ft_exit(hub, 1),
			NULL);
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->ea = NULL;
	mlx->no = NULL;
	mlx->we = NULL;
	mlx->so = NULL;
	mlx->no_path = NULL;
	mlx->so_path = NULL;
	mlx->we_path = NULL;
	mlx->ea_path = NULL;
	mlx->floor_color = 0;
	mlx->ceil_color = 0;
	return (mlx);
}
