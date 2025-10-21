/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:59:55 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/13 14:07:29 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_info *info, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1])
		return (ft_error("env", "too many arguments"), 1);
	while (info->env[i])
	{
		ft_printf(1, "%s\n", info->env[i]);
		i++;
	}
	return (0);
}
