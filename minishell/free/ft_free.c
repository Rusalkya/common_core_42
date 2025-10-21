/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:53:00 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/17 10:28:29 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_ppl(t_ppl *ppl)
{
	int	i;

	i = 0;
	if (ppl == NULL)
		return ;
	free_2(&ppl->paths);
	if (ppl->path_name != NULL)
		free(ppl->path_name);
	if (ppl->lst_pid != NULL)
		free(ppl->lst_pid);
	while (i < ppl->nb_fd)
	{
		free(ppl->fd[i]);
		i++;
	}
	free(ppl->fd);
	free(ppl);
}

void	free_info(t_info *info)
{
	if (info == NULL)
		return ;
	free_2(&info->exp);
	free_2(&info->env);
	free(info);
}

void	free_out(t_out *out)
{
	t_out	*out_swap;

	if (out == NULL)
		return ;
	while (out)
	{
		if (out->file)
			free(out->file);
		out_swap = out;
		out = out->next;
		free(out_swap);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*cmd_swap;

	if (cmd == NULL)
		return ;
	while (cmd != NULL)
	{
		if (cmd->args)
			free_2(&cmd->args);
		if (cmd->file_in)
			free_2(&cmd->file_in);
		if (cmd->file_out)
			free_out(cmd->file_out);
		if (cmd->heredoc)
			free_2(&cmd->heredoc);
		cmd_swap = cmd;
		cmd = cmd->next;
		free(cmd_swap);
	}
}
