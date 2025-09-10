/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:02:05 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:06:40 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

static void	exception(t_info *info, char *new)
{
	char	*dst;

	info->env = malloc(sizeof(char *) * 2);
	if (!info->env)
		ft_exit();
	dst = malloc(ft_strlen(new) + 1);
	if (!dst)
		ft_exit();
	ft_strcpy(dst, new);
	info->env[0] = dst;
	info->env[1] = NULL;
}

void	ft_add_env(t_info *info, char *new)
{
	int		i;
	char	**new_info;
	char	*dst;

	if (!info->env)
		return (exception(info, new));
	new_info = malloc(sizeof(char *) * (ft_strlen_y(info->env) + 2));
	if (!new_info)
		ft_exit();
	i = 0;
	while (info->env[i])
	{
		new_info[i] = info->env[i];
		i++;
	}
	dst = malloc(ft_strlen(new) + 1);
	if (!dst)
		ft_exit();
	ft_strcpy(dst, new);
	new_info[i] = dst;
	new_info[i + 1] = NULL;
	free(info->env);
	info->env = new_info;
}
