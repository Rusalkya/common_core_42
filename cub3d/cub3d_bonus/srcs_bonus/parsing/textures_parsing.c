/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:41:03 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 17:56:48 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	*ft_strdup_2(char *s)
{
	char	*dst;
	size_t	i;
	size_t	j;

	dst = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] == '\r' || s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i] != '\n' && s[i] != '\0' && s[i] != '\t' && s[i] != ' ')
	{
		dst[j] = s[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	while (s[i] == '\t' || s[i] == ' ')
		i++;
	if (s[i] != '\0' && s[i] != '\n')
		return (free(dst), NULL);
	return (dst);
}

static int	read_path_wall_2(t_hub *hub, char *trim)
{
	hub->mlx->ea_path = ft_strdup_2(trim);
	if (!hub->mlx->ea_path)
		return (msg_error("Wall east", "invalide parameter", NULL), 0);
	return (1);
}

static int	read_path_wall(t_hub *hub, char *trim, int dir)
{
	skip_whitespace(&trim);
	if (dir == NORTH)
	{
		hub->mlx->no_path = ft_strdup_2(trim);
		if (!hub->mlx->no_path)
			return (msg_error("Wall north", "invalide parameter", NULL), 0);
	}
	else if (dir == SOUTH)
	{
		hub->mlx->so_path = ft_strdup_2(trim);
		if (!hub->mlx->so_path)
			return (msg_error("Wall south", "invalide parameter", NULL), 0);
	}
	else if (dir == WEST)
	{
		hub->mlx->we_path = ft_strdup_2(trim);
		if (!hub->mlx->we_path)
			return (msg_error("Wall west", "invalide parameter", NULL), 0);
	}
	else if (dir == EAST)
		return (read_path_wall_2(hub, trim));
	return (0);
}

int	wall_check(t_hub *hub, char *trim)
{
	if (ft_strncmp(trim, "NO ", 3) == 0)
		return (read_path_wall(hub, &trim[3], NORTH));
	else if (ft_strncmp(trim, "SO ", 3) == 0)
		return (read_path_wall(hub, &trim[3], SOUTH));
	else if (ft_strncmp(trim, "WE ", 3) == 0)
		return (read_path_wall(hub, &trim[3], WEST));
	else if (ft_strncmp(trim, "EA ", 3) == 0)
		return (read_path_wall(hub, &trim[3], EAST));
	else
		return (0);
	return (1);
}
