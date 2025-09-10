/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:29:15 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/24 13:06:08 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

void	ft_cd(t_cmd *cd, t_info *info)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (g_error = 1, ft_error("getcwd", strerror(errno)));
	if (chdir(cd->src[0]) == -1)
		return (free(path), g_error = 1, ft_error("chdir", strerror(errno)));
	ft_update_env("OLDPWD", path, info);
	free(path);
	path = getcwd(NULL, 0);
	if (!path)
		return (g_error = 1, ft_error("getcwd", strerror(errno)));
	ft_update_env("PWD", path, info);
	free(path);
}
