/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:40:20 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 11:37:31 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	error_env(t_info *info, int i)
{
	while (i >= 0)
	{
		free(info->env[i]);
		info->env[i] = NULL;
		i--;
	}
	free(info->env);
	info->env = NULL;
}

static void	exception(t_hub *hub, t_info *info)
{
	info->env = malloc(sizeof(char *) * 1);
	if (!info->env)
		return (ft_error("creat exp", strerror(errno)), ft_exit(hub, 1));
	info->env[0] = NULL;
}

void	ft_creat_env(t_hub *hub, t_info *info, char **envp)
{
	int	i;

	if (!envp || !envp[0])
		return (exception(hub, info));
	info->env = malloc(sizeof(char *) * (ft_strlen_y(envp) + 1));
	if (!info->env)
		return (ft_error("creat env", strerror(errno)), ft_exit(hub, 1));
	i = 0;
	while (envp[i])
	{
		info->env[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!info->env[i])
		{
			error_env(info, i - 1);
			return (ft_error("creat env", strerror(errno)), ft_exit(hub, 1));
		}
		ft_strcpy(info->env[i], envp[i]);
		i++;
	}
	info->env[i] = NULL;
}
