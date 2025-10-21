/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:29:15 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 14:01:49 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_home(t_hub *hub, t_info *info, char **all_path)
{
	char	*home;

	home = ft_getenv(hub, info, "HOME");
	if (!home)
		return (free(*all_path), ft_error("HOME not set", NULL), 1);
	if (chdir(home) == -1)
	{
		free(home);
		return (free(*all_path), ft_error("chdir", strerror(errno)), 1);
	}
	return (free(home), 0);
}

static int	update_pwd(t_hub *hub, t_info *info)
{
	char	*path;
	char	*all_path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_error("getcwd", strerror(errno)), 1);
	all_path = ft_strjoin("PWD=", path);
	if (!all_path)
	{
		free(path);
		return (ft_error("strjoin", strerror(errno)), ft_exit(hub, 1), 1);
	}
	ft_update_env(hub, info, all_path);
	ft_update_export(hub, info, all_path);
	free(path);
	free(all_path);
	return (0);
}

int	ft_cd(t_hub *hub, t_cmd *cmd, t_info *info)
{
	char	*path;
	char	*all_path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ft_error("getcwd", strerror(errno)), 1);
	all_path = ft_strjoin("OLDPWD=", path);
	if (!all_path)
	{
		free(path);
		return (ft_error("strjoin", strerror(errno)), ft_exit(hub, 1), 1);
	}
	free(path);
	if (cmd->args[1] == NULL)
	{
		if (cd_home(hub, info, &all_path) != 0)
			return (1);
	}
	else if (cmd->args[2] != NULL)
		return (free(all_path), ft_error("cd", "too many arguments"), 1);
	else if (chdir(cmd->args[1]) == -1)
		return (free(all_path), ft_error("chdir", strerror(errno)), 1);
	ft_update_env(hub, info, all_path);
	ft_update_export(hub, info, all_path);
	return (free(all_path), update_pwd(hub, info));
}
