/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:25:07 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/17 10:27:41 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	children_2(t_hub *hub, t_info *info, t_cmd *cmd, t_ppl *ppl)
{
	signals_child();
	if (cmd->std_in == 1 && cmd->fd_in != 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	else if (ppl->i_fd != 0)
		dup2(ppl->fd[ppl->i_fd - 1][0], STDIN_FILENO);
	if (cmd->fd_out != 0)
		dup2(cmd->fd_out, STDOUT_FILENO);
	else if (ppl->i_fd != ppl->nb_fd - 1)
		dup2(ppl->fd[ppl->i_fd][1], STDOUT_FILENO);
	if (ppl->i_fd != 0)
		close(ppl->fd[ppl->i_fd - 1][0]);
	close(ppl->fd[ppl->i_fd][0]);
	close(ppl->fd[ppl->i_fd][1]);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 0)
		close(cmd->fd_out);
	if (verif_built_in(cmd->args[0]) == 0)
		ft_exit(hub, ft_built_in(hub, info, cmd));
	execve(ppl->path_name, cmd->args, info->env);
	ft_error("execve", strerror(errno));
	if (errno == EACCES)
		ft_exit(hub, 126);
	ft_exit(hub, 1);
}

static int	children(t_hub *hub, t_info *info, t_cmd *cmd, t_ppl *ppl)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ppl->error = 1, ft_error("fork", strerror(errno)), 1);
	if (pid == 0)
		children_2(hub, info, cmd, ppl);
	ppl->lst_pid[ppl->i_pd] = pid;
	ppl->i_pd++;
	return (exec_end(cmd, ppl), 0);
}

static int	exec(t_hub *hub, t_info *info, t_cmd *cmd, t_ppl *ppl)
{
	int		j;

	j = 0;
	if (heredoc(cmd, ppl) != 0)
		j++;
	if (ppl->error != 0)
		return (1);
	if (files(cmd) != 0)
		return (close_files(cmd), 1);
	if (ppl->error != 0)
		return (close_files(cmd), 1);
	if (!cmd->args)
	{
		close_files(cmd);
		return (0);
	}
	if (verif_built_in(cmd->args[0]) == 0 && cmd->next == NULL && cmd->i == 0)
		return (built_in(hub, hub->info, cmd));
	if (pipe(ppl->fd[ppl->i_fd]) == -1)
		return (close_files(cmd), pipe_error(ppl), 1);
	if (j == 0 && find_command(hub, ppl, cmd->args) == 0)
		return (children(hub, info, cmd, ppl));
	return (exec_end(cmd, ppl), 1);
}

static int	pipeline_2(t_hub *hub, int error)
{
	if (hub->ppl->i_fd - 1 >= 0)
		close(hub->ppl->fd[hub->ppl->i_fd - 1][0]);
	signals_parent_wait();
	if (hub->cmd && hub->ppl->error == 1)
		return (ft_wait(hub, hub->ppl), ft_exit(hub, 1), 1);
	if (hub->ppl->error == 0)
	{
		if (error == 0)
			return (ft_wait(hub, hub->ppl));
		else
			return (ft_wait(hub, hub->ppl), error);
	}
	return (ft_wait(hub, hub->ppl), hub->ppl->error);
}

int	pipeline(t_hub *hub)
{
	int	error;

	error = 0;
	if (setting_exec(hub, hub->cmd, hub->ppl) != 0)
		return (pipeline_end(hub, hub->ppl->error), hub->ppl->error);
	while (hub->cmd)
	{
		hub->ppl->error = 0;
		error = exec(hub, hub->info, hub->cmd, hub->ppl);
		if (hub->ppl->error == 1 || hub->ppl->error == 130)
			break ;
		free_exec(hub, hub->ppl);
	}
	return (pipeline_2(hub, error));
}
