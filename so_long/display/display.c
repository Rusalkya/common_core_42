/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:49:09 by clfouger          #+#    #+#             */
/*   Updated: 2025/07/22 10:13:42 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_move_count(t_game *g)
{
	char	*count;
	char	*label;

	count = ft_itoa(g->move_count);
	if (!count)
		return ;
	label = ft_strjoin("moves: ", count);
	free(count);
	if (!label)
		return ;
	mlx_string_put(g->mlx, g->win, (g->width - 1) * TILE_SIZE + 10, 10,
		0xFFFFFF, label);
	free(label);
}
