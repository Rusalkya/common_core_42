/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:25:01 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/27 11:14:43 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_hub	*hub;

	hub = creat_hub();
	parse_cub_file(argc, argv, hub);
	init(hub, hub->mlx);
	init_mouse(hub);
	mlx_hook(hub->mlx->win, 17, 0, destroy, hub);
	mlx_hook(hub->mlx->win, 2, 1L << 0, key_press, hub);
	mlx_hook(hub->mlx->win, 3, 1L << 1, key_release, hub);
	mlx_hook(hub->mlx->win, 6, 1L << 6, mouse_move, hub);
	mlx_hook(hub->mlx->win, 4, 1L << 2, mouse_click, hub);
	mlx_loop_hook(hub->mlx->mlx, frame, hub);
	mlx_loop(hub->mlx->mlx);
	return ((void)argv, 0);
}
