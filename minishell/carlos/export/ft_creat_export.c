/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:03:45 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:07:34 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

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

void	ft_creat_export(t_info *info, char **envp)
{
	int	i;

	if (!envp)
		return ;
	info->exp = malloc(sizeof(char *) * (list_height(envp) + 1));
	if (!info->exp)
		return (g_error = 1, ft_error("malloc export", NULL));
	i = 0;
	while (envp[i])
	{
		info->exp[i] = malloc(ft_strlen(envp[i]) + 1);
		if (!info->exp[i])
			return (error_exp(info, i - 1), ft_error("malloc export", NULL));
		ft_strcpy(info->exp[i], envp[i]);
		i++;
	}
	info->exp[i] = NULL;
}
