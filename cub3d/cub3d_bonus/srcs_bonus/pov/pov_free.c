/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:21:28 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 12:56:38 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	free_pov_empty_hammer(t_hub *hub)
{
	if (hub->pov->empty1 && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->empty1->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->empty1->ptr);
		free(hub->pov->empty1);
	}
	if (hub->pov->empty2 && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->empty2->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->empty2->ptr);
		free(hub->pov->empty2);
	}
	if (hub->pov->hammer1 && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->hammer1->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->hammer1->ptr);
		free(hub->pov->hammer1);
	}
	if (hub->pov->hammer2 && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->hammer2->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->hammer2->ptr);
		free(hub->pov->hammer2);
	}
}

static void	free_pov_hit_sprites(t_hub *hub)
{
	if (hub->pov->hammer_hit1 && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->hammer_hit1->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->hammer_hit1->ptr);
		free(hub->pov->hammer_hit1);
	}
	if (hub->pov->hammer_hit2 && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->hammer_hit2->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->hammer_hit2->ptr);
		free(hub->pov->hammer_hit2);
	}
	if (hub->pov->hammer_hit3 && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->hammer_hit3->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->hammer_hit3->ptr);
		free(hub->pov->hammer_hit3);
	}
}

static void	free_pov_effect_sprites(t_hub *hub)
{
	if (hub->pov->hammer_pow && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->hammer_pow->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->hammer_pow->ptr);
		free(hub->pov->hammer_pow);
	}
	if (hub->pov->hammer_crack && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->hammer_crack->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->hammer_crack->ptr);
		free(hub->pov->hammer_crack);
	}
	if (hub->pov->hammer_boom && hub->mlx && hub->mlx->mlx)
	{
		if (hub->pov->hammer_boom->ptr)
			mlx_destroy_image(hub->mlx->mlx, hub->pov->hammer_boom->ptr);
		free(hub->pov->hammer_boom);
	}
}

void	free_pov(t_hub *hub)
{
	if (!hub->pov)
		return ;
	free_pov_empty_hammer(hub);
	free_pov_hit_sprites(hub);
	free_pov_effect_sprites(hub);
	free(hub->pov);
}
