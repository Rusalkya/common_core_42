/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:32:47 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/23 15:57:42 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_player_images(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->player_base[i].img)
			mlx_destroy_image(g->mlx, g->player_base[i].img);
		if (g->player_run[i].frame1)
			mlx_destroy_image(g->mlx, g->player_run[i].frame1);
		if (g->player_run[i].frame2)
			mlx_destroy_image(g->mlx, g->player_run[i].frame2);
		i++;
	}
}

static void	free_villain_images(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->villain_base[i].img)
			mlx_destroy_image(g->mlx, g->villain_base[i].img);
		i++;
	}
}

static void	free_images(t_game *g)
{
	free_villain_images(g);
	if (g->item.img)
		mlx_destroy_image(g->mlx, g->item.img);
	if (g->floor.img)
		mlx_destroy_image(g->mlx, g->floor.img);
	if (g->wall_1.img)
		mlx_destroy_image(g->mlx, g->wall_1.img);
	if (g->wall_3.img)
		mlx_destroy_image(g->mlx, g->wall_3.img);
	if (g->wall_dd.img)
		mlx_destroy_image(g->mlx, g->wall_dd.img);
	if (g->wall_gg.img)
		mlx_destroy_image(g->mlx, g->wall_gg.img);
	if (g->wall_d.img)
		mlx_destroy_image(g->mlx, g->wall_d.img);
	if (g->wall_g.img)
		mlx_destroy_image(g->mlx, g->wall_g.img);
	if (g->exit.img)
		mlx_destroy_image(g->mlx, g->exit.img);
	if (g->noexit.img)
		mlx_destroy_image(g->mlx, g->noexit.img);
}

int	clean_everything(t_game *g)
{
	if (!g)
		return (0);
	if (g->mlx)
	{
		free_player_images(g);
		free_images(g);
	}
	if (g->win && g->mlx)
	{
		mlx_destroy_window(g->mlx, g->win);
		g->win = NULL;
	}
	if (g->map)
	{
		free_map(g->map);
		g->map = NULL;
	}
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
		g->mlx = NULL;
	}
	return (0);
}
