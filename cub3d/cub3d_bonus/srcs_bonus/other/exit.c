/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:37:35 by cade-jes          #+#    #+#             */
/*   Updated: 2025/12/02 16:12:30 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	destroy(t_hub *hub)
{
	ft_exit(hub, 0);
	return (0);
}

static void	free_mlx_2(t_hub *hub)
{
	free(hub->mlx->no_path);
	free(hub->mlx->so_path);
	free(hub->mlx->we_path);
	free(hub->mlx->ea_path);
	if (hub->mlx->win && hub->mlx->mlx)
		mlx_destroy_window(hub->mlx->mlx, hub->mlx->win);
	if (hub->mlx->mlx)
	{
		mlx_destroy_display(hub->mlx->mlx);
		free(hub->mlx->mlx);
	}
	free(hub->mlx);
}

static void	free_mlx(t_hub *hub)
{
	int	i;

	if (!hub->mlx)
		return ;
	free_basic_textures(hub);
	free_crack_textures(hub);
	free_hole_textures(hub);
	free_sprite_textures(hub);
	i = 0;
	while (i < 3)
	{
		if (hub->mlx->screamers[i] && hub->mlx->mlx)
		{
			if (hub->mlx->screamers[i]->ptr)
				mlx_destroy_image(hub->mlx->mlx, hub->mlx->screamers[i]->ptr);
			free(hub->mlx->screamers[i]);
		}
		i++;
	}
	free_mlx_2(hub);
}

void	ft_exit(t_hub *hub, int i)
{
	if (!hub)
		exit(i);
	stop_all_sounds(hub);
	if (hub->key)
		free(hub->key);
	if (hub->map)
		free_2(&hub->map);
	if (hub->frame && hub->mlx && hub->mlx->mlx)
		mlx_destroy_image(hub->mlx->mlx, hub->frame->ptr);
	if (hub->frame)
		free(hub->frame);
	if (hub->hammers)
		free_hammers(hub->hammers);
	if (hub->pov)
		free_pov(hub);
	if (hub->mlx)
		free_mlx(hub);
	if (hub->player)
		free(hub->player);
	if (hub->ray)
		free(hub->ray);
	free(hub);
	exit(i);
}
