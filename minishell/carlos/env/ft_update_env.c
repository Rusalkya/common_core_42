/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:53:08 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:07:12 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

static int	verif_value(char *new)
{
	int	i = 0;

	while (new[i] && new[i] != '=')
		i++;
	if (!new[i])
		return (1);
	if (new[i + 1] == '\0')
		return (1);
	return (0);
}

void	ft_update_env(t_info *info, char *new)
{
	int		i;
	char	*dst;

	if (verif_value(new) != 0)
		return ;
	if (!info->env) 
		return (ft_add_env(info, new));
	i = 0;
	while (info->env[i])
	{
		if (ft_strcmp_equal(new, info->env[i]) == 0)
			break ;
		i++;
	}
	if (!info->env[i])
		return (ft_add_env(info, new));
	free(info->env[i]);
	dst = malloc(ft_strlen(new) + 1);
	if (!dst)
		return (g_error = 1, ft_error("malloc update_env", NULL));
	ft_strcpy(dst, new);
	info->env[i] = dst;
}
