/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:38:16 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 12:35:40 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	verif_file_in_2(t_cmd *cmd, char *file)
{
	if (access(file, F_OK) == -1)
		return (ft_error(file, strerror(errno)), 1);
	else if (access(file, R_OK) == -1)
		return (ft_error(file, strerror(errno)), 1);
	else
		cmd->fd_in = open(file, O_RDONLY);
	if (cmd->fd_in < 0)
		return (ft_error(file, strerror(errno)), 1);
	return (0);
}

static int	verif_file_in(t_cmd *cmd)
{
	int		i;
	int		j;

	if (!cmd->file_in || !cmd->file_in[0])
		return (0);
	i = 0;
	j = 0;
	if (cmd->file_in == NULL)
		return (1);
	while (cmd->file_in[i] != NULL)
	{
		if (cmd->fd_in != 0)
		{
			close(cmd->fd_in);
			cmd->fd_in = 0;
		}
		if (verif_file_in_2(cmd, cmd->file_in[i]) != 0)
			j++;
		i++;
	}
	return (j);
}

static int	verif_file_out_2(t_cmd *cmd, char *file, int type)
{
	if (type == 0)
	{
		if (access(file, F_OK) == -1)
			cmd->fd_out = open(file, O_CREAT | O_WRONLY, 0644);
		else if (access(file, W_OK) == -1)
			return (ft_error(file, strerror(errno)), 1);
		else
			cmd->fd_out = open(file, O_WRONLY | O_TRUNC);
		if (cmd->fd_out < 0)
			return (ft_error(file, strerror(errno)), 1);
	}
	else
	{
		if (access(file, F_OK) == -1)
			cmd->fd_out = open(file, O_CREAT | O_WRONLY, 0644);
		else if (access(file, W_OK) == -1)
			return (ft_error(file, strerror(errno)), 1);
		else
			cmd->fd_out = open(file, O_WRONLY | O_APPEND);
		if (cmd->fd_out < 0)
			return (ft_error(file, strerror(errno)), 1);
	}
	return (0);
}

static int	verif_file_out(t_cmd *cmd)
{
	int		j;
	t_out	*file_out;

	if (!cmd->file_out || !cmd->file_out->file)
		return (0);
	j = 0;
	file_out = cmd->file_out;
	while (file_out != NULL)
	{
		if (cmd->fd_out != 0)
		{
			close(cmd->fd_out);
			cmd->fd_out = 0;
		}
		if (verif_file_out_2(cmd, file_out->file, file_out->type) != 0)
			j++;
		file_out = file_out->next;
	}
	return (j);
}

int	files(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (verif_file_in(cmd) != 0)
		i++;
	if (verif_file_out(cmd) != 0)
		i++;
	return (i);
}
