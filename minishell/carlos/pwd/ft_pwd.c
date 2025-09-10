/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:33:25 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:08:45 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		ft_printf(1, "%s\n", path);
		free(path);
	}
	ft_error("getcwd", strerror(errno));
	g_error = 1;
}
