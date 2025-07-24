/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:29:49 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/22 10:28:50 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_next_villain_pos(int phase, int *x, int *y)
{
	if (phase == 0)
		(*y)++;
	else if (phase == 1)
		(*x)++;
	else if (phase == 2)
		(*y)--;
	else if (phase == 3)
		(*x)--;
}

static void	animate_villain(t_game *g)
{
	static int	phase = 0;
	static int	step = 0;
	int			next_x;
	int			next_y;

	if (g->villain_x == 0 && g->villain_y == 0)
		return ;
	next_x = g->villain_x;
	next_y = g->villain_y;
	get_next_villain_pos(phase, &next_x, &next_y);
	if (step < 3 && g->map[next_y][next_x] != '1')
	{
		g->villain_x = next_x;
		g->villain_y = next_y;
		step++;
	}
	else
	{
		phase = (phase + 1) % 4;
		step = 0;
	}
}

int	game_loop(t_game *g)
{
	static int	frame_count;

	frame_count++;
	if (frame_count < 15000)
		return (0);
	frame_count = 0;
	animate_villain(g);
	if (g->player_x == g->villain_x && g->player_y == g->villain_y)
	{
		ft_putstr_fd("GAME OVER\n", 2);
		clean_everything(g);
		exit(0);
	}
	map_setting(g);
	return (0);
}
