/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:03:45 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 11:36:34 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	error_exp(t_info *info, int i)
{
	while (i >= 0)
	{
		free(info->exp[i]);
		info->exp[i] = NULL;
		i--;
	}
	free(info->exp);
	info->exp = NULL;
}

static void	exception(t_hub *hub, t_info *info)
{
	info->exp = malloc(sizeof(char *) * 1);
	if (!info->exp)
		return (ft_error("creat exp", strerror(errno)), ft_exit(hub, 1));
	info->exp[0] = NULL;
}

void	ft_creat_export(t_hub *hub, t_info *info, char **envp)
{
	int	i;

	if (!envp || !envp[0])
		return (exception(hub, info));
	info->exp = malloc(sizeof(char *) * (ft_strlen_y(envp) + 1));
	if (!info->exp)
		return (ft_error("creat exp", strerror(errno)), ft_exit(hub, 1));
	i = 0;
	while (envp[i])
	{
		info->exp[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!info->exp[i])
		{
			error_exp(info, i - 1);
			return (ft_error("creat exp", strerror(errno)), ft_exit(hub, 1));
		}
		ft_strcpy(info->exp[i], envp[i]);
		i++;
	}
	info->exp[i] = NULL;
	ft_sort_export(info);
}
