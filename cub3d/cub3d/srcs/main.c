/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:25:01 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/27 15:39:42 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_hub	*hub;

	hub = creat_hub();
	parse_cub_file(argc, argv, hub);
	init(hub, hub->mlx);
	init_player(hub);
	mlx_hook(hub->mlx->win, 17, 0, destroy, hub);
	mlx_hook(hub->mlx->win, 2, 1L << 0, key_press, hub);
	mlx_hook(hub->mlx->win, 3, 1L << 1, key_release, hub);
	mlx_loop_hook(hub->mlx->mlx, frame, hub);
	mlx_loop(hub->mlx->mlx);
	return ((void)argv, 0);
}
