/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:19:25 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 11:12:28 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_for_shell.h"

int		nb_error = 0;

s_info	*creat_info(void)
{
	s_info	*info;

	info = malloc(sizeof(s_info));
	if (!info)
		return (ft_error("malloc info", NULL), NULL);
	info->env = NULL;
	info->exp = NULL;
	return (info);
}

int	main(int argc, char **argv, char **env)
{
	s_info	*info;

	info = creat_info();
	if (!info)
		return (1);
	int	i = 0;
	ft_creat_env(info, env);
	if (nb_error == 1)
		return (1);
	while (info->env[i])
	{
		ft_printf(1, "%s\n", info->env[i]);
		i++;
	}
	ft_printf(1, "\n\n\n");
	return (0);
}
