/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:52:08 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/22 15:52:39 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	rotate_player_angle(t_player *player, double angle)
{
	double	old_dirx;
	double	old_planex;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(angle);
	sin_rot = sin(angle);
	old_dirx = player->dirx;
	old_planex = player->planex;
	player->dirx = player->dirx * cos_rot - player->diry * sin_rot;
	player->diry = old_dirx * sin_rot + player->diry * cos_rot;
	player->planex = player->planex * cos_rot - player->planey * sin_rot;
	player->planey = old_planex * sin_rot + player->planey * cos_rot;
}

int	mouse_move(int x, int y, t_hub *hub)
{
	int		delta_x;
	double	angle;

	(void)y;
	delta_x = x - MOUSE_X;
	if (delta_x == 0)
		return (0);
	angle = (double)delta_x * MOUSE_SENS;
	rotate_player_angle(hub->player, angle);
	mlx_mouse_move(hub->mlx->mlx, hub->mlx->win, MOUSE_X, MOUSE_Y);
	return (0);
}

void	init_mouse(t_hub *hub)
{
	mlx_mouse_hide(hub->mlx->mlx, hub->mlx->win);
	mlx_mouse_move(hub->mlx->mlx, hub->mlx->win, MOUSE_X, MOUSE_Y);
}
