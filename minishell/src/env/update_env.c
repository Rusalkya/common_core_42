/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:53:08 by cade-jes          #+#    #+#             */
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

void	ft_update_env(char *var, char *value, t_info *info)
{
	int		i;
	char	*new_value;
	size_t	var_len;

	if (!info->env)
		return;
	var_len = ft_strlen(var);
	new_value = ft_strjoin(var, "=");
	if (!new_value)
		return;
	new_value = ft_strjoin_free(new_value, value);
	if (!new_value)
		return;
	
	i = 0;
	while (info->env[i])
	{
		if (ft_strncmp(info->env[i], var, var_len) == 0 && info->env[i][var_len] == '=')
		{
			free(info->env[i]);
			info->env[i] = new_value;
			return;
		}
		i++;
	}
	ft_add_env(new_value, info);
	free(new_value);
}
