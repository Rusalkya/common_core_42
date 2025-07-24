/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:57:57 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/23 16:00:03 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_game *g, void *img, int x, int y)
{
	if (!img)
		ft_printf("img test (NULL) à x=%d y=%d\n", x, y);
	if (!g->mlx)
		ft_printf("mlx test\n");
	if (!g->win)
		ft_printf("win test\n");
	mlx_put_image_to_window(g->mlx, g->win, img, x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_exit(t_game *g, char c, int x, int y)
{
	if (c == 'E')
	{
		if (g->collected_items == g->total_items)
			draw_tile(g, g->exit.img, x, y);
		else
			draw_tile(g, g->noexit.img, x, y);
	}
}

void	draw_wall_sprite(t_game *g, int x, int y)
{
	int	last_row;
	int	last_col;

	last_row = g->height - 1;
	last_col = g->width - 1;
	if (y == 0 && x == 0)
		draw_tile(g, g->wall_gg.img, x, y);
	else if (y == 0 && x == last_col)
		draw_tile(g, g->wall_dd.img, x, y);
	else if (y == last_row && x == 0)
		draw_tile(g, g->wall_g.img, x, y);
	else if (y == last_row && x == last_col)
		draw_tile(g, g->wall_d.img, x, y);
	else if (x == 0)
		draw_tile(g, g->wall_gg.img, x, y);
	else if (x == last_col)
		draw_tile(g, g->wall_dd.img, x, y);
	else if (y == 0 || y == last_row)
		draw_tile(g, g->wall_1.img, x, y);
	else
		draw_tile(g, g->wall_3.img, x, y);
}

static void	set_map(t_game *g)
{
	if (g->villain_x && g->villain_y)
		draw_tile(g, g->villain_base[g->villain_dir].img, g->villain_x,
			g->villain_y);
	if (g->player_frame == 0)
		draw_tile(g, g->player_run[g->player_dir].frame1, g->player_x,
			g->player_y);
	else
		draw_tile(g, g->player_run[g->player_dir].frame2, g->player_x,
			g->player_y);
	display_move_count(g);
}

void	map_setting(t_game *g)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			c = g->map[y][x];
			if (g->floor.img)
				draw_tile(g, g->floor.img, x, y);
			if (c == '1')
				draw_wall_sprite(g, x, y);
			else if (c == 'C')
				draw_tile(g, g->item.img, x, y);
			else if (c == 'E')
				render_exit(g, c, x, y);
			x++;
		}
		y++;
	}
	set_map(g);
}
