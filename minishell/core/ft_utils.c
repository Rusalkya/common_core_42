/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:57:15 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/15 11:06:39 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_built_in(char *arg)
{
	if (ft_strcmp(arg, "echo") == 0)
		return (0);
	if (ft_strcmp(arg, "cd") == 0)
		return (0);
	if (ft_strcmp(arg, "pwd") == 0)
		return (0);
	if (ft_strcmp(arg, "export") == 0)
		return (0);
	if (ft_strcmp(arg, "unset") == 0)
		return (0);
	if (ft_strcmp(arg, "env") == 0)
		return (0);
	if (ft_strcmp(arg, "exit") == 0)
		return (0);
	return (1);
}

void	exec_end(t_cmd *cmd, t_ppl *ppl)
{
	if (ppl->i_fd != 0)
		close(ppl->fd[ppl->i_fd - 1][0]);
	close(ppl->fd[ppl->i_fd][1]);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 0)
		close(cmd->fd_out);
	ppl->i_fd++;
}

void	pipeline_end(t_hub *hub, int error)
{
	free_cmd(hub->cmd);
	free_ppl(hub->ppl);
	creat_ppl(hub);
	hub->ppl->error = error;
}

void	pipe_error(t_ppl *ppl)
{
	if (ppl->i_fd != 0)
		close(ppl->fd[ppl->i_fd - 1][0]);
	return (ppl->error = 1, ft_error("pipe", strerror(errno)));
}

void	close_files(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 0)
		close(cmd->fd_out);
}
