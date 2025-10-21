/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:01:34 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/14 18:59:57 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_option(char **args, int *i)
{
	int	j;

	if (args[*i][0] != '-' || args[*i][1] != 'n')
		return (1);
	j = 1;
	while (args[*i][j] == 'n')
		j++;
	if (args[*i][j] != 0)
		return (1);
	while (args[*i])
	{
		j = 1;
		if (args[*i][0] != '-' || args[*i][1] == 0)
			break ;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != 0)
			break ;
		(*i)++;
	}
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->args[1] == NULL || verif_option(cmd->args, &i) != 0)
	{
		while (cmd->args[i])
		{
			ft_printf(1, "%s", cmd->args[i]);
			if (cmd->args[i + 1])
				ft_printf(1, " ");
			i++;
		}
		ft_printf(1, "\n");
		return (0);
	}
	while (cmd->args[i])
	{
		ft_printf(1, "%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(1, " ");
		i++;
	}
	return (0);
}
