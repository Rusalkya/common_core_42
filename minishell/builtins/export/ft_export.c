/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:15:46 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 16:44:17 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static int	verif_export_2(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha((unsigned char)str[0]) == 0 && str[0] != '_')
		return (1);
	i = 1;
	while (str[i] && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
	{
		if (ft_isalnum((unsigned char)str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '\0' || str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
		return (0);
	return (1);
}

static int	verif_export(t_hub *hub, t_info *info, t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	if (verif_export_2(cmd->args[i]) != 0)
		return (1);
	while (cmd->args[i][j] && cmd->args[i][j] != '+')
		j++;
	if (cmd->args[i][j] == '+')
		export_condition(hub, info, cmd, i);
	return (0);
}

static void	ft_export_2(t_hub *hub, t_info *info, t_cmd *cmd, int i)
{
	if (find_egual(cmd->args[i]) != 0)
		return ;
	ft_update_export(hub, info, cmd->args[i]);
	if (its_empty(cmd->args[i]) == 0)
	{
		if (does_it_exist_env(info, cmd->args[i]) != 0)
			ft_add_env(hub, info, cmd->args[i]);
		else
			ft_update_env(hub, info, cmd->args[i]);
	}
}

int	ft_export(t_hub *hub, t_info *info, t_cmd *cmd)
{
	int	i;
	int	j;

	if (!cmd->args[1])
		return (print_export(info), 0);
	j = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (verif_export(hub, info, cmd, i) != 0)
		{
			ft_error("export", "not a valid identifier");
			j = 1;
		}
		else if (does_it_exist(info, cmd->args[i]) != 0)
		{
			ft_add_export(hub, info, cmd->args[i]);
			if (its_empty(cmd->args[i]) == 0)
				ft_add_env(hub, info, cmd->args[i]);
		}
		else
			ft_export_2(hub, info, cmd, i);
		i++;
	}
	return (j);
}
