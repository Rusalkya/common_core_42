/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:15:46 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:07:50 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

int	ft_strcmp_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if ((s1[i] == '=' || s1[i] == 0) && (s2[i] == '=' || s2[i] == 0))
		return (0);
	if (s2[i] == '=')
		return (1);
	if (s1[i] == '=')
		return (-1);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

static int	does_it_exist(char *src, t_info *info)
{
	int i;

	i = 0;
	while (info->exp[i])
	{
		if (ft_strcmp_equal(src, info->exp[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	print_export(t_info *info)
{
	int	i;

	i = 0;
	while (info->exp[i])
	{
		ft_printf(1, "%s\n", info->exp[i]);
		i++;
	}
}

void	ft_export(t_cmd *cmd, t_info *info)
{
	int	i;
	int	j;

	if (!cmd->src)
		return (print_export(info));
	i = 0;
	while (cmd->src[i])
	{
		if (does_it_exist(cmd->src[i], info) != 0)
			ft_add_export(cmd->src[i], info);
		else
			ft_update_export(cmd->src[i], info);
		i++;
	}
}
