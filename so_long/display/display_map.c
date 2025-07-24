/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:13:09 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/22 10:27:44 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	load_wall_images(t_game *g)
{
	g->wall_1.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/wall/wall_1.xpm", &g->wall_1.width, &g->wall_1.height);
	g->wall_3.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/wall/wall_3.xpm", &g->wall_3.width, &g->wall_3.height);
	g->wall_dd.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/wall/wall_dd.xpm", &g->wall_dd.width, &g->wall_dd.height);
	g->wall_d.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/wall/wall_d.xpm", &g->wall_d.width, &g->wall_d.height);
	g->wall_g.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/wall/wall_g.xpm", &g->wall_g.width, &g->wall_gg.height);
	g->wall_gg.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/wall/wall_gg.xpm", &g->wall_gg.width, &g->wall_gg.height);
	if (!g->wall_1.img || !g->wall_3.img || !g->wall_gg.img
		|| !g->wall_g.img || !g->wall_d.img || !g->wall_dd.img)
		return (ft_putstr_fd("error: failed to load wall sprites\n", 2), 1);
	return (0);
}

int	load_other_images(t_game *g)
{
	g->floor.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/floor.xpm", &g->floor.width, &g->floor.height);
	g->noexit.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/noexit.xpm", &g->noexit.width, &g->noexit.height);
	g->exit.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/exit.xpm", &g->exit.width, &g->exit.height);
	g->item.img = mlx_xpm_file_to_image(g->mlx,
			"sprite/item.xpm", &g->item.width, &g->item.height);
	if (!g->floor.img || !g->exit.img || !g->noexit.img || !g->item.img)
		return (ft_putstr_fd("error: failed to load some sprites\n", 2), 1);
	return (0);
}

void	update_exit_sprite(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == 'E')
			{
				if (g->collected_items == g->total_items)
					g->exit.img = g->exit.img;
				else
					g->exit.img = g->noexit.img;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	check_items(t_game *g, int x, int y)
{
	if (g->map[y][x] == 'C')
	{
		g->map[y][x] = '0';
		g->collected_items++;
	}
	if (g->map[y][x] == 'E' && g->collected_items == g->total_items)
	{
		ft_putstr_fd("Bravo, MELON va pouvoir depenser toutes ses gems\n", 1);
		clean_everything(g);
		exit(0);
	}
}
