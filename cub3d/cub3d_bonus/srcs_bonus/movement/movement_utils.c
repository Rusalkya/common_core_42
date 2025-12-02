/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:30:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/26 10:21:03 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_dir_factors(double dir_factors[5][4])
{
	dir_factors[0][0] = 0;
	dir_factors[0][1] = 0;
	dir_factors[0][2] = 0;
	dir_factors[0][3] = 0;
	dir_factors[1][0] = 1;
	dir_factors[1][1] = 1;
	dir_factors[1][2] = 0;
	dir_factors[1][3] = 0;
	dir_factors[2][0] = -1;
	dir_factors[2][1] = -1;
	dir_factors[2][2] = 0;
	dir_factors[2][3] = 0;
	dir_factors[3][0] = 0;
	dir_factors[3][1] = 0;
	dir_factors[3][2] = 1;
	dir_factors[3][3] = -1;
	dir_factors[4][0] = 0;
	dir_factors[4][1] = 0;
	dir_factors[4][2] = -1;
	dir_factors[4][3] = 1;
}

void	apply_movement(t_hub *hub, double new_x, double new_y)
{
	char	cell_y;
	char	cell_x;

	cell_y = hub->map[(int)new_y][(int)hub->player->posx];
	cell_x = hub->map[(int)hub->player->posy][(int)new_x];
	if (cell_y != '1' && cell_y != '2' && cell_y != '3' && cell_y != '4')
		hub->player->posy = new_y;
	if (cell_x != '1' && cell_x != '2' && cell_x != '3' && cell_x != '4')
		hub->player->posx = new_x;
}
