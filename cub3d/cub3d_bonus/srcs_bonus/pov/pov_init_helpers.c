/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov_init_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:50:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 10:26:20 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_img	*load_pov_image(t_hub *hub, char *path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
	{
		msg_error("Malloc error for POV image.", NULL, NULL);
		ft_exit(hub, 1);
	}
	img->ptr = mlx_xpm_file_to_image(hub->mlx->mlx, path, &img->w, &img->h);
	if (!img->ptr)
	{
		free(img);
		msg_error("Failed to load POV image:", path, NULL);
		ft_exit(hub, 1);
	}
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line,
			&img->endian);
	return (img);
}

void	init_pov_struct(t_hub *hub)
{
	hub->pov = malloc(sizeof(t_pov));
	if (!hub->pov)
	{
		msg_error("Malloc error for POV.", NULL, NULL);
		ft_exit(hub, 1);
	}
	hub->pov->empty1 = NULL;
	hub->pov->empty2 = NULL;
	hub->pov->hammer1 = NULL;
	hub->pov->hammer2 = NULL;
	hub->pov->hammer_hit1 = NULL;
	hub->pov->hammer_hit2 = NULL;
	hub->pov->hammer_hit3 = NULL;
	hub->pov->hammer_pow = NULL;
	hub->pov->hammer_crack = NULL;
	hub->pov->hammer_boom = NULL;
	hub->pov->current_frame = 0;
	hub->pov->frame_counter = 0;
	hub->pov->animation_speed = 10;
	hub->pov->is_attacking = 0;
	hub->pov->attack_frame = 0;
	hub->pov->attack_type = 0;
	hub->is_moving = 0;
}
