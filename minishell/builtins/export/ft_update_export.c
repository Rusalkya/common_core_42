/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:55:17 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/01 13:31:00 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_update_export(t_hub *hub, t_info *info, char *new)
{
	int		i;
	char	*dst;

	if (!info->exp)
		return (ft_add_export(hub, info, new));
	i = 0;
	while (info->exp[i])
	{
		if (ft_strcmp_equal(new, info->exp[i]) == 0)
			break ;
		i++;
	}
	if (!info->exp[i])
		return (ft_add_export(hub, info, new));
	free(info->exp[i]);
	dst = malloc(ft_strlen(new) + 1);
	if (!dst)
		return (ft_error("update exp", strerror(errno)), ft_exit(hub, 1));
	ft_strcpy(dst, new);
	info->exp[i] = dst;
}
