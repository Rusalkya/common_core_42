/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:55:17 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:08:21 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

void	ft_update_export(char *new, t_info *info)
{
	int		i;
	char	*dst;

	if (!info->exp) 
		return (ft_add_export(info, new));
	i = 0;
	while (info->exp[i])
	{
		if (ft_strcmp_equal(new, info->exp[i]) == 0)
			break ;
		i++;
	}
	if (!info->exp[i])
		return (ft_add_export(info, new));
	free(info->exp[i]);
	dst = malloc(ft_strlen(new) + 1);
	if (!dst)
		return (g_error = 1, ft_error("malloc update_export", NULL));
	ft_strcpy(dst, new);
	info->exp[i] = dst;
}
