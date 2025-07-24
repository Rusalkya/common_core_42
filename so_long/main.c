/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:17:55 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/23 16:02:25 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (ft_putstr_fd("error: failed to initialize mlx\n", 2), 1);
	g->win = mlx_new_window(g->mlx, g->width * TILE_SIZE, g->height * TILE_SIZE,
			"So Long");
	if (!g->win)
		return (ft_putstr_fd("error: failed to create window\n", 2), 1);
	if (load_wall_images(g) || load_other_images(g) || load_player_images(g)
		|| load_villain_images(g))
	{
		clean_everything(g);
		return (1);
	}
	find_player(g);
	find_villain(g);
	return (0);
}

static int	clean_everything_and_exit(t_game *g)
{
	clean_everything(g);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (ft_putstr_fd("error: choose corrects files\n", 2), 1);
	ft_memset(&g, 0, sizeof(t_game));
	if (game_is_ok(&g, argv[1]))
		return (1);
	if (init_game(&g))
		return (clean_everything(&g), 1);
	map_setting(&g);
	mlx_hook(g.win, 17, 0, clean_everything_and_exit, &g);
	mlx_key_hook(g.win, handle_input_player, &g);
	mlx_loop_hook(g.mlx, game_loop, &g);
	mlx_loop(g.mlx);
	return (0);
}
