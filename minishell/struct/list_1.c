/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:25:59 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/15 18:56:22 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_info(t_hub *hub)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (ft_error("info", strerror(errno)), ft_exit(hub, 1));
	info->env = NULL;
	info->exp = NULL;
	hub->info = info;
}

void	creat_ppl(t_hub *hub)
{
	t_ppl	*ppl;

	ppl = malloc(sizeof(t_ppl));
	if (!ppl)
		return (ft_error("ppl", strerror(errno)), ft_exit(hub, 1));
	ppl->paths = NULL;
	ppl->path_name = NULL;
	ppl->lst_pid = NULL;
	ppl->error = 0;
	ppl->fd = NULL;
	ppl->nb_fd = 0;
	ppl->i_fd = 0;
	ppl->i_pd = 0;
	hub->ppl = ppl;
}

void	creat_rl(t_hub *hub)
{
	t_rl	*shell;

	shell = malloc(sizeof(t_rl));
	if (!shell)
		return (ft_error("shell", strerror(errno)), ft_exit(hub, 1));
	shell->input = NULL;
	shell->prompt = "minishell$ ";
	shell->exit_status = 0;
	shell->gc = NULL;
	hub->rl = shell;
}

t_hub	*creat_hub(char **envp)
{
	t_hub	*hub;

	hub = malloc(sizeof(t_hub));
	if (!hub)
		return (ft_error("hub", strerror(errno)), ft_exit(hub, 1), NULL);
	hub->cmd = NULL;
	hub->info = NULL;
	hub->ppl = NULL;
	hub->gc = NULL;
	hub->token = NULL;
	hub->rl = NULL;
	hub->quote = NULL;
	hub->last_value = 0;
	creat_info(hub);
	creat_ppl(hub);
	creat_rl(hub);
	ft_creat_env(hub, hub->info, envp);
	ft_creat_export(hub, hub->info, envp);
	return (hub);
}
