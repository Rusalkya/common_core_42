/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:47:12 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 11:14:43 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	skip_whitespace(char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

int	handle_color_line(t_hub *h, char *trim)
{
	int		kind;
	char	*arg;
	int		col;

	kind = 0;
	if (ft_strncmp(trim, "F ", 2) == 0)
		kind = 1;
	else if (ft_strncmp(trim, "C ", 2) == 0)
		kind = 2;
	if (!kind)
		return (0);
	arg = trim + 1;
	skip_whitespace(&arg);
	col = get_color(h, arg);
	if (col < 0)
	{
		msg_error("Invalid RGB value (must be 0-255)", arg, NULL);
		return (-1);
	}
	if (kind == 1)
		h->mlx->floor_color = (unsigned int)col;
	else
		h->mlx->ceil_color = (unsigned int)col;
	return (1);
}

void	free_map_array(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	process_line(t_hub *hub, char *line, t_map_data *data)
{
	char	*trim;
	int		color_result;

	trim = line;
	skip_whitespace(&trim);
	if (wall_check(hub, trim))
		return (1);
	if (!data->map_started)
	{
		color_result = handle_color_line(hub, trim);
		if (color_result < 0)
			return (-1);
		if (color_result > 0)
			return (1);
	}
	data->map = process_map_line(data->map, line, &data->line_count,
			&data->map_started);
	if (!data->map)
		return (-1);
	return (0);
}
