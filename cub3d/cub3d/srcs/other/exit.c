/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:37:35 by cade-jes          #+#    #+#             */
/*   Updated: 2025/11/25 14:03:32 by cade-jes         ###   ########.fr       */
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
	if (!hub->mlx)
		return ;
	if (hub->mlx->ea && hub->mlx->mlx)
	{
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->ea->ptr);
		free(hub->mlx->ea);
	}
	if (hub->mlx->we && hub->mlx->mlx)
	{
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->we->ptr);
		free(hub->mlx->we);
	}
	if (hub->mlx->no && hub->mlx->mlx)
	{
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->no->ptr);
		free(hub->mlx->no);
	}
	if (hub->mlx->so && hub->mlx->mlx)
	{
		mlx_destroy_image(hub->mlx->mlx, hub->mlx->so->ptr);
		free(hub->mlx->so);
	}
	free_mlx_2(hub);
}

void	ft_exit(t_hub *hub, int i)
{
	if (!hub)
		exit(i);
	if (hub->key)
		free(hub->key);
	if (hub->map)
		free_2(&hub->map);
	if (hub->frame && hub->mlx && hub->mlx->mlx)
		mlx_destroy_image(hub->mlx->mlx, hub->frame->ptr);
	if (hub->frame)
		free(hub->frame);
	if (hub->mlx)
		free_mlx(hub);
	if (hub->player)
		free(hub->player);
	if (hub->ray)
		free(hub->ray);
	free(hub);
	exit(i);
}
