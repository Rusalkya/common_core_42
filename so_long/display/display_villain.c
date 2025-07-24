/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_villain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:40:56 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/17 10:59:18 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	find_villain(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == 'V')
			{
				g->villain_x = x;
				g->villain_y = y;
				g->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	load_villain_images(t_game *g)
{
	g->villain_base[0].img = mlx_xpm_file_to_image(g->mlx,
			"sprite/ghost/ghost_down.xpm",
			&g->villain_base[0].width, &g->villain_base[0].height);
	g->villain_base[1].img = mlx_xpm_file_to_image(g->mlx,
			"sprite/ghost/ghost_up.xpm",
			&g->villain_base[1].width, &g->villain_base[1].height);
	g->villain_base[2].img = mlx_xpm_file_to_image(g->mlx,
			"sprite/ghost/ghost_left.xpm",
			&g->villain_base[2].width, &g->villain_base[2].height);
	g->villain_base[3].img = mlx_xpm_file_to_image(g->mlx,
			"sprite/ghost/ghost_right.xpm",
			&g->villain_base[3].width, &g->villain_base[3].height);
	if (!g->villain_base[0].img || !g->villain_base[1].img
		|| !g->villain_base[2].img || !g->villain_base[3].img)
		return (ft_putstr_fd("error: failed loading villain\n", 2), 1);
	return (0);
}
