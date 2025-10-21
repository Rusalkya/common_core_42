/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:03:02 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 16:39:53 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_egual(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	its_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (0);
	return (1);
}

static int	export_condition_2(t_hub *hub, t_info *info, t_cmd *cmd, int i)
{
	char	*copy;
	int		j;
	int		x;

	j = 0;
	x = 0;
	copy = malloc(ft_strlen(cmd->args[i]));
	if (!copy)
		return (ft_error("export_+", strerror(errno)), ft_exit(hub, 1), 1);
	while (cmd->args[i][j])
	{
		if (cmd->args[i][j] == '+')
			j++;
		copy[x] = cmd->args[i][j];
		x++;
		j++;
	}
	copy[x] = 0;
	free(cmd->args[i]);
	cmd->args[i] = copy;
	if (does_it_exist(info, cmd->args[i]) != 0)
		return (1);
	return (0);
}

void	export_condition(t_hub *hub, t_info *info, t_cmd *cmd, int i)
{
	char	*copy;
	char	*str;
	int		j;
	int		x;

	j = -1;
	x = -1;
	if (export_condition_2(hub, info, cmd, i) != 0)
		return ;
	str = ft_getenv(hub, info, cmd->args[i]);
	copy = malloc(ft_strlen(str) + ft_strlen(cmd->args[i]));
	if (!copy)
		return (free(str), ft_error("exp_+", strerror(errno)), ft_exit(hub, 1));
	while (str[++x])
		copy[x] = str[x];
	while (cmd->args[i][j] != '=')
		j++;
	while (cmd->args[i][++j])
	{
		copy[x] = cmd->args[i][j];
		x++;
	}
	free(str);
}
