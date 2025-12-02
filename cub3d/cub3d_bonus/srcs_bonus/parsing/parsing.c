/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:35:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/26 11:51:26 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	validate_args(t_hub *hub, int argc)
{
	if (argc < 2)
	{
		msg_error("Error: Not enough arguments", NULL, NULL);
		ft_exit(hub, EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		msg_error("Error: Too many arguments", NULL, NULL);
		ft_exit(hub, EXIT_FAILURE);
	}
}

static void	validate_file_format(t_hub *hub, char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
	{
		msg_error("Error: Invalid file format. Expected .cub file", NULL, NULL);
		ft_exit(hub, EXIT_FAILURE);
	}
}

void	parse_cub_file(int argc, char **argv, t_hub *hub)
{
	if (!hub)
		return ;
	validate_args(hub, argc);
	validate_file_format(hub, argv[1]);
	hub->map = read_map_from_file(argv[1], hub);
	if (!hub->map)
	{
		msg_error("Error: Failed to read map from file", NULL, NULL);
		ft_exit(hub, 1);
	}
	check_map_char(hub);
	check_player(hub->map, hub);
	check_map_closed(hub);
	init_player(hub);
}
