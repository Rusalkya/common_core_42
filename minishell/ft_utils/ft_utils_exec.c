/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:34:38 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 14:21:54 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exec(t_hub *hub, t_ppl *ppl)
{
	t_cmd	*swap;

	swap = hub->cmd->next;
	free_2(&hub->cmd->args);
	free_2(&hub->cmd->file_in);
	free_2(&hub->cmd->heredoc);
	free_out(hub->cmd->file_out);
	free(hub->cmd);
	hub->cmd = swap;
	if (ppl->path_name != NULL)
		free(ppl->path_name);
	ppl->path_name = NULL;
}

static int	count_struct(t_cmd *cmd)
{
	int		i;
	int		j;
	t_cmd	*test;

	i = 0;
	test = cmd;
	while (test)
	{
		j = 0;
		if (test->heredoc)
		{
			while (test->heredoc[j])
			{
				j++;
				i++;
			}
		}
		test = test->next;
		i++;
	}
	return (i);
}

static void	creat_pipe(t_hub *hub, t_cmd *cmd, t_ppl *ppl)
{
	int	i;
	int	nb;

	nb = count_struct(cmd);
	ppl->nb_fd = nb;
	ppl->fd = malloc(sizeof(int *) * nb);
	if (!ppl->fd)
		return (ft_error("malloc pipe", strerror(errno)), ft_exit(hub, 1));
	i = 0;
	while (i < nb)
	{
		ppl->fd[i] = malloc(sizeof(int) * 2);
		if (!ppl->fd[i])
		{
			while (--i >= 0)
				free(ppl->fd[i]);
			return (ft_error("malloc pipe", strerror(errno)), ft_exit(hub, 1));
		}
		i++;
	}
}

void	count_list(t_cmd *cmd)
{
	int		i;
	t_cmd	*trash;

	i = 0;
	trash = cmd;
	while (trash)
	{
		trash->i = i;
		trash = trash->next;
		i++;
	}
}

int	setting_exec(t_hub *hub, t_cmd *cmd, t_ppl *ppl)
{
	int		i;
	t_cmd	*test;
	char	*path;

	count_list(cmd);
	i = 0;
	test = cmd;
	while (test)
	{
		test = test->next;
		i++;
	}
	ppl->lst_pid = malloc(sizeof(pid_t) * i);
	if (!ppl->lst_pid)
		return (ft_error("malloc pid", strerror(errno)), ft_exit(hub, 1), 1);
	creat_pipe(hub, cmd, ppl);
	path = ft_getenv(hub, hub->info, "PATH=");
	if (!path)
		return (ppl->paths = NULL, free(path), 0);
	ppl->paths = ft_split(path, ':');
	free(path);
	if (!ppl->paths)
		return (ft_error("split path", strerror(errno)), ft_exit(hub, 1), 1);
	return (0);
}
