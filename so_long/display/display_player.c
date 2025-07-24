/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:12:37 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/17 17:49:40 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	load_player_images(t_game *g)
{
	g->player_base[0].img = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_basic_down.xpm", &g->player_base[0].width,
			&g->player_base[0].height);
	g->player_base[1].img = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_basic_up.xpm", &g->player_base[1].width,
			&g->player_base[1].height);
	g->player_base[2].img = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_basic_left.xpm", &g->player_base[2].width,
			&g->player_base[2].height);
	g->player_base[3].img = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_basic_right.xpm", &g->player_base[3].width,
			&g->player_base[3].height);
	if (!g->player_base[0].img || !g->player_base[1].img
		|| !g->player_base[2].img || !g->player_base[3].img)
		return (ft_putstr_fd("error: failed loading player base\n", 2), 1);
	if (load_player_animsud(g) || load_player_animslr(g))
		return (1);
	return (0);
}

int	load_player_animsud(t_game *g)
{
	g->player_run[0].frame1 = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_run_down1.xpm", &g->player_run[0].width,
			&g->player_run[0].height);
	g->player_run[0].frame2 = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_run_down2.xpm", &g->player_run[0].width,
			&g->player_run[0].height);
	g->player_run[1].frame1 = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_run_up1.xpm", &g->player_run[1].width,
			&g->player_run[1].height);
	g->player_run[1].frame2 = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_run_up2.xpm", &g->player_run[1].width,
			&g->player_run[1].height);
	if (!g->player_run[0].frame1 || !g->player_run[0].frame2
		|| !g->player_run[1].frame1 || !g->player_run[1].frame2)
		return (ft_putstr_fd("error: failed loading player anim\n", 2), 1);
	return (0);
}

int	load_player_animslr(t_game *g)
{
	g->player_run[2].frame1 = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_run_left1.xpm", &g->player_run[2].width,
			&g->player_run[2].height);
	g->player_run[2].frame2 = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_run_left2.xpm", &g->player_run[2].width,
			&g->player_run[2].height);
	g->player_run[3].frame1 = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_run_right1.xpm", &g->player_run[3].width,
			&g->player_run[3].height);
	g->player_run[3].frame2 = mlx_xpm_file_to_image(g->mlx,
			"sprite/fox/fox_run_right2.xpm", &g->player_run[3].width,
			&g->player_run[3].height);
	if (!g->player_run[2].frame1 || !g->player_run[2].frame2
		|| !g->player_run[3].frame1 || !g->player_run[3].frame2)
		return (ft_putstr_fd("error: failed loading player anim\n", 2), 1);
	return (0);
}

void	find_player(t_game *g)
{
	int		y;
	int		x;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == 'P')
			{
				g->player_x = x;
				g->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
