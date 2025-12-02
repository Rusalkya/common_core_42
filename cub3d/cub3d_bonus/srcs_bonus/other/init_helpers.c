/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:50:53 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 10:24:52 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		load_wall(t_mlx *mlx, t_img *img, char *path);
void	free_image_extended(t_hub *hub, int i);

void	load_stain_sprites(t_hub *hub, int *error_level)
{
	int		i;
	char	path[50];

	i = 0;
	while (i < 6)
	{
		snprintf(path, sizeof(path), "textures/stains/blood%d.xpm", i + 1);
		if (load_wall(hub->mlx, hub->mlx->stains[i], path))
		{
			*error_level = 13 + i;
			return ;
		}
		i++;
	}
	*error_level = -1;
}
