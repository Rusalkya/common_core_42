/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:40:20 by cade-jes          #+#    #+#             */
/*   Updated: 2025/09/11 12:07:59 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	g_error = 1;
}

static int	list_height(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	ft_creat_env(t_info *info, char **envp)
{
	int	i;

	if (!envp)
		return ;
	info->env = malloc(sizeof(char *) * (list_height(envp) + 1));
	if (!info->env)
		return (g_error = 1, ft_error("malloc env", NULL));
	i = 0;
	while (envp[i])
	{
		info->env[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!info->env[i])
			return (error_env(info, i - 1), ft_error("malloc env", NULL));
		ft_strcpy(info->env[i], envp[i]);
		i++;
	}
	info->env[i] = NULL;
}
