/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:10:54 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 10:27:08 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <sys/wait.h>
#include <signal.h>

void	play_hammer_sound(void)
{
	play_sound("hammer_hit.wav");
}

void	play_air_hit_sound(void)
{
	play_sound("air_hit.wav");
}

void	play_screamer_sound(void)
{
	static int	alternate = 0;

	if (alternate % 2 == 0)
		play_sound("screamer.wav");
	else
		play_sound("screamer1.wav");
	alternate++;
}
