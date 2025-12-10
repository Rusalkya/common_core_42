/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:46:18 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/24 09:43:50 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	read_lines_loop(int fd, t_hub *hub, t_map_data *data)
{
	char	*line;
	char	*tmp;
	int		result;

	line = get_next_line(fd);
	while (line)
	{
		result = process_line(hub, line, data);
		free(line);
		if (result == -1)
		{
			tmp = get_next_line(fd);
			while (tmp)
			{
				free(tmp);
				tmp = get_next_line(fd);
			}
			close(fd);
			if (data->map)
				free_map_array(data->map);
			ft_exit(hub, 1);
		}
		line = get_next_line(fd);
	}
}

char	**read_map_from_file(char *filename, t_hub *hub)
{
	int			fd;
	t_map_data	data;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		msg_error("Error opening file", NULL, NULL);
		ft_exit(hub, 1);
	}
	data.map = malloc(sizeof(char *));
	if (!data.map)
	{
		msg_error("malloc failed", NULL, NULL);
		ft_exit(hub, 1);
	}
	data.map[0] = NULL;
	data.map_started = 0;
	data.line_count = 0;
	read_lines_loop(fd, hub, &data);
	close(fd);
	return (data.map);
}
