/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:02:05 by cade-jes          #+#    #+#             */
/*   Updated: 2025/09/11 12:07:59 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strlen_y(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static void	exception(t_info *info, char *src)
{
	char	*dst;

	info->env = malloc(sizeof(char *) * 2);
	if (!info->env)
		return (g_error = 1, ft_error("malloc", NULL));
	dst = malloc(ft_strlen(src) + 1);
	if (!dst)
	{
		free(info->env);
		info->env = NULL;
		return (g_error = 1, ft_error("malloc", NULL));
	}
	ft_strcpy(dst, src);
	info->env[0] = dst;
	info->env[1] = NULL;
}

void	ft_add_env(char *src, t_info *info)
{
	int		i;
	char	**new_env;
	char	*dst;

	if (!info->env)
		return (exception(info, src));
	new_env = malloc(sizeof(char *) * (ft_strlen_y(info->env) + 2));
	if (!new_env)
		return (g_error = 1, ft_error("malloc", NULL));
	i = 0;
	while (info->env[i])
	{
		new_env[i] = info->env[i];
		i++;
	}
	dst = malloc(ft_strlen(src) + 1);
	if (!dst)
	{
		free(new_env);
		return (g_error = 1, ft_error("malloc", NULL));
	}
	ft_strcpy(dst, src);
	new_env[i] = dst;
	new_env[i + 1] = NULL;
	free(info->env);
	info->env = new_env;
}
