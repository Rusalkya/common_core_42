/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:40:30 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 11:43:39 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_line_env(t_hub *hub, t_info *info, char *str)
{
	int		i;
	int		j;
	char	**new_info;

	new_info = malloc(sizeof(char *) * (ft_strlen_y(info->env) + 1));
	if (!new_info)
		return (ft_error("rm line env", strerror(errno)), ft_exit(hub, 1));
	i = 0;
	j = 0;
	while (info->env[i])
	{
		if (ft_strcmp_equal(str, info->env[i]) == 0)
			free(info->env[i]);
		else
		{
			new_info[j] = info->env[i];
			j++;
		}
		i++;
	}
	new_info[j] = NULL;
	if (info->env)
		free(info->env);
	info->env = new_info;
}

int	does_it_exist_env(t_info *info, char *src)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		if (ft_strcmp_equal(src, info->env[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	remove_line_exp(t_hub *hub, t_info *info, char *str)
{
	int		i;
	int		j;
	char	**new_info;

	new_info = malloc(sizeof(char *) * (ft_strlen_y(info->exp)));
	if (!new_info)
		return (ft_error("rm line exp", strerror(errno)), ft_exit(hub, 1));
	i = 0;
	j = 0;
	while (info->exp[i])
	{
		if (ft_strcmp_equal(str, info->exp[i]) == 0)
			free(info->exp[i]);
		else
		{
			new_info[j] = info->exp[i];
			j++;
		}
		i++;
	}
	new_info[j] = NULL;
	free(info->exp);
	info->exp = new_info;
}

int	ft_unset(t_hub *hub, t_info *info, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args == NULL)
		return (0);
	while (cmd->args[i])
	{
		if (does_it_exist(info, cmd->args[i]) == 0)
		{
			remove_line_exp(hub, info, cmd->args[i]);
			if (does_it_exist_env(info, cmd->args[i]) == 0)
				remove_line_env(hub, info, cmd->args[i]);
		}
		i++;
	}
	return (0);
}
