/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:29:51 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/22 10:28:31 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_player_dir(int key, t_game *g)
{
	if (key == XK_w || key == XK_W || key == XK_Up)
		g->player_dir = 1;
	else if (key == XK_s || key == XK_S || key == XK_Down)
		g->player_dir = 0;
	else if (key == XK_a || key == XK_A || key == XK_Left)
		g->player_dir = 2;
	else if (key == XK_d || key == XK_D || key == XK_Right)
		g->player_dir = 3;
}

static int	update_player_pos(int key, int *x, int *y)
{
	if (key == XK_w || key == XK_W || key == XK_Up)
		(*y)--;
	else if (key == XK_s || key == XK_S || key == XK_Down)
		(*y)++;
	else if (key == XK_a || key == XK_A || key == XK_Left)
		(*x)--;
	else if (key == XK_d || key == XK_D || key == XK_Right)
		(*x)++;
	else
		return (0);
	return (1);
}

static void	check_villain_collision(t_game *g)
{
	if (g->player_x == g->villain_x && g->player_y == g->villain_y)
	{
		ft_putstr_fd("GAME OVER\n", 2);
		clean_everything(g);
		exit(0);
	}
}

int	handle_input_player(int key, t_game *g)
{
	int	x;
	int	y;

	x = g->player_x;
	y = g->player_y;
	update_player_dir(key, g);
	if (key == XK_Escape)
	{
		clean_everything(g);
		exit(0);
	}
	if (!update_player_pos(key, &x, &y))
		return (0);
	if (ft_strchr("1", g->map[y][x]))
		return (0);
	g->player_x = x;
	g->player_y = y;
	check_villain_collision(g);
	g->move_count++;
	g->player_frame = !g->player_frame;
	ft_printf("moves de MELON : %d\n", g->move_count);
	check_items(g, x, y);
	map_setting(g);
	return (0);
}
