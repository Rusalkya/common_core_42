/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:33:04 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/14 18:01:52 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	*find_texture(t_hub *hub, const char *name)
{
	const char	*dirs[] = {"textures", NULL};
	int			i;
	size_t		len;
	char		*p;

	i = 0;
	while (dirs[i])
	{
		len = strlen(dirs[i]) + 1 + strlen(name) + 1;
		p = malloc(len);
		if (!p)
		{
			msg_error("malloc failed for texture path", NULL, NULL);
			ft_exit(hub, 1);
		}
		snprintf(p, len, "%s/%s", dirs[i], name);
		if (access(p, F_OK) == 0)
			return (p);
		free(p);
		i++;
	}
	msg_error("Texture not found", (char *)name, NULL);
	ft_exit(hub, 1);
	return (NULL);
}

void	load_img(t_hub *hub)
{
	if (!hub)
		return ;
	hub->mlx->no_path = find_texture(hub, "wallNO.xpm");
	hub->mlx->so_path = find_texture(hub, "wallSO.xpm");
	hub->mlx->we_path = find_texture(hub, "wallWE.xpm");
	hub->mlx->ea_path = find_texture(hub, "wallEA.xpm");
	hub->mlx->floor_color = 0x004F2E;
	hub->mlx->ceil_color = 0x0E002E;
}

static void	load_single_texture(t_hub *hub, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(hub->mlx->mlx, path, &img->w, &img->h);
	if (img->ptr)
		img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line,
				&img->endian);
}

static void	check_textures_loaded(t_hub *hub)
{
	if (!hub->mlx->no->ptr || !hub->mlx->so->ptr || !hub->mlx->ea->ptr
		|| !hub->mlx->we->ptr)
	{
		msg_error("Failed to load one or more textures", NULL, NULL);
		ft_exit(hub, 1);
	}
}

void	load_textures(t_hub *hub)
{
	if (!hub)
		return ;
	if (!hub->mlx->mlx)
		hub->mlx->mlx = mlx_init();
	if (!hub->mlx->mlx)
	{
		msg_error("mlx_init failed", NULL, NULL);
		ft_exit(hub, 1);
	}
	load_single_texture(hub, hub->mlx->no, hub->mlx->no_path);
	load_single_texture(hub, hub->mlx->so, hub->mlx->so_path);
	load_single_texture(hub, hub->mlx->ea, hub->mlx->ea_path);
	load_single_texture(hub, hub->mlx->we, hub->mlx->we_path);
	check_textures_loaded(hub);
}
