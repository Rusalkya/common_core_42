/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:50:04 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/22 16:56:32 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	get_move_speed(t_hub *hub)
{
	double	speed;

	speed = MOVE_SPEED;
	if (hub->key->ctrl)
		speed *= 1.5;
	return (speed);
}

void	rotate_player(t_player *player, int direction)
{
	double	old_dirx;
	double	old_planex;
	double	cos_rot;
	double	sin_rot;

	if (direction == 1)
	{
		cos_rot = cos(ROT_SPEED);
		sin_rot = sin(ROT_SPEED);
	}
	else
	{
		cos_rot = cos(-ROT_SPEED);
		sin_rot = sin(-ROT_SPEED);
	}
	old_dirx = player->dirx;
	old_planex = player->planex;
	player->dirx = player->dirx * cos_rot - player->diry * sin_rot;
	player->diry = old_dirx * sin_rot + player->diry * cos_rot;
	player->planex = player->planex * cos_rot - player->planey * sin_rot;
	player->planey = old_planex * sin_rot + player->planey * cos_rot;
}

void	move_player(t_hub *hub, int direction)
{
	double	dir_factors[5][4];
	double	new_x;
	double	new_y;
	double	speed;

	init_dir_factors(dir_factors);
	if (direction < 1 || direction > 4)
		return ;
	speed = get_move_speed(hub);
	if (direction <= 2)
	{
		new_y = hub->player->posy + hub->player->diry * speed
			* dir_factors[direction][0];
		new_x = hub->player->posx + hub->player->dirx * speed
			* dir_factors[direction][1];
	}
	else
	{
		new_x = hub->player->posx + hub->player->diry * speed
			* dir_factors[direction][2];
		new_y = hub->player->posy + hub->player->dirx * speed
			* dir_factors[direction][3];
	}
	play_footstep_sound(hub);
	apply_movement(hub, new_x, new_y);
}

int	key_release(int keybord, t_hub *hub)
{
	if (keybord == XK_w)
		hub->key->w = 0;
	else if (keybord == XK_a)
		hub->key->a = 0;
	else if (keybord == XK_s)
		hub->key->s = 0;
	else if (keybord == XK_d)
		hub->key->d = 0;
	else if (keybord == XK_Right)
		hub->key->r = 0;
	else if (keybord == XK_Left)
		hub->key->l = 0;
	else if (keybord == XK_Control_L || keybord == XK_Control_R)
		hub->key->ctrl = 0;
	return (0);
}

int	key_press(int keybord, t_hub *hub)
{
	if (keybord == XK_Escape)
		ft_exit(hub, 0);
	else if (keybord == XK_w)
		hub->key->w = 1;
	else if (keybord == XK_a)
		hub->key->a = 1;
	else if (keybord == XK_s)
		hub->key->s = 1;
	else if (keybord == XK_d)
		hub->key->d = 1;
	else if (keybord == XK_Right)
		hub->key->r = 1;
	else if (keybord == XK_Left)
		hub->key->l = 1;
	else if (keybord == XK_Control_L || keybord == XK_Control_R)
		hub->key->ctrl = 1;
	return (0);
}
