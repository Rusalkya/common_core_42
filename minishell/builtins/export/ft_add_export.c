/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:53:15 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/15 13:46:13 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exception(t_hub *hub, t_info *info, char *new)
{
	char	*dst;

	info->exp = malloc(sizeof(char *) * 2);
	if (!info->exp)
		return (ft_error("add exp", strerror(errno)), ft_exit(hub, 1));
	dst = malloc(ft_strlen(new) + 1);
	if (!dst)
		return (ft_error("add exp", strerror(errno)), ft_exit(hub, 1));
	ft_strcpy(dst, new);
	info->exp[0] = dst;
	info->exp[1] = NULL;
}

void	ft_add_export(t_hub *hub, t_info *info, char *new)
{
	int		i;
	char	**new_info;
	char	*dst;

	if (!info->exp)
		return (exception(hub, info, new));
	new_info = malloc(sizeof(char *) * (ft_strlen_y(info->exp) + 2));
	if (!new_info)
		return (ft_error("add exp", strerror(errno)), ft_exit(hub, 1));
	i = 0;
	while (info->exp[i])
	{
		new_info[i] = info->exp[i];
		i++;
	}
	dst = malloc(ft_strlen(new) + 1);
	if (!dst)
	{
		free(new_info);
		return (ft_error("add exp", strerror(errno)), ft_exit(hub, 1));
	}
	ft_strcpy(dst, new);
	new_info[i] = dst;
	new_info[i + 1] = NULL;
	return (free(info->exp), info->exp = new_info, ft_sort_export(info));
}
