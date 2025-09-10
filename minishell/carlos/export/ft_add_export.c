/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:53:15 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:07:21 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

static void	exception(t_info *info, char *new)
{
	char	*dst;

	info->exp = malloc(sizeof(char *) * 2);
	if (!info->exp)
		ft_exit();
	dst = malloc(ft_strlen(new) + 1);
	if (!dst)
		ft_exit();
	ft_strcpy(dst, new);
	info->exp[0] = dst;
	info->exp[1] = NULL;
}

void	ft_add_export(t_info *info, char *new)
{
	int		i;
	char	**new_info;
	char	*dst;

	if (!info->exp)
		return (exception(info, new));
	new_info = malloc(sizeof(char *) * (ft_strlen_y(info->exp) + 2));
	if (!new_info)
		ft_exit();
	i = 0;
	while (info->exp[i])
	{
		new_info[i] = info->exp[i];
		i++;
	}
	dst = malloc(ft_strlen(new) + 1);
	if (!dst)
		ft_exit();
	ft_strcpy(dst, new);
	new_info[i] = dst;
	new_info[i + 1] = NULL;
	free(info->exp);
	info->exp = new_info;
	return (ft_sort_export(info));
}
