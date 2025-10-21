/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 19:59:58 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 14:22:05 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_built_in_2(t_hub *hub, t_info *info, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(hub, cmd, info));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(hub, info, cmd));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(hub, info, cmd));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(info, cmd));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit_bi(hub));
	return (1);
}

int	built_in(t_hub *hub, t_info *info, t_cmd *cmd)
{
	int	saved_out;
	int	ret;

	saved_out = -1;
	if (cmd->fd_out > 1)
	{
		saved_out = dup(STDOUT_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
	}
	close_files(cmd);
	ret = ft_built_in_2(hub, info, cmd);
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
	return (ret);
}

int	ft_built_in(t_hub *hub, t_info *info, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(hub, cmd, info));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(hub, info, cmd));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(hub, info, cmd));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(info, cmd));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(hub, 0), 0);
	return (1);
}
