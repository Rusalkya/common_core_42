/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:33:55 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 17:11:53 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_hd(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
}

static int	ctrl_c_hd(t_cmd *cmd, t_ppl *ppl, char **str)
{
	free(*str);
	g_sig = 0;
	ppl->error = 130;
	sig_inter();
	return (exec_end(cmd, ppl), 1);
}

static int	heredoc_3(t_cmd *cmd, t_ppl *ppl)
{
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		ppl->error = 130;
		close(ppl->fd[ppl->i_fd][0]);
		return (exec_end(cmd, ppl), 1);
	}
	return (exec_end(cmd, ppl), 0);
}

static int	heredoc_2(t_cmd *cmd, t_ppl *ppl)
{
	char	*str;

	if (pipe(ppl->fd[ppl->i_fd]) == -1)
		return (pipe_error(ppl), 1);
	signals_heredoc();
	while (1)
	{
		str = get_next_line(0);
		if (g_sig == SIGINT)
			return (ctrl_c_hd(cmd, ppl, &str));
		if (!str)
			return (sig_inter(), heredoc_3(cmd, ppl));
		if (ft_strncmp(str, cmd->heredoc[cmd->i_hd],
				ft_strlen(cmd->heredoc[cmd->i_hd])) == 0
			&& str[ft_strlen(cmd->heredoc[cmd->i_hd])] == '\n')
			break ;
		ft_putstr_fd(str, ppl->fd[ppl->i_fd][1]);
		free(str);
		str = NULL;
	}
	sig_inter();
	return (free(str), exec_end(cmd, ppl), 0);
}

int	heredoc(t_cmd *cmd, t_ppl *ppl)
{
	int	j;

	j = 0;
	if (cmd->heredoc == NULL)
		return (0);
	cmd->i_hd = 0;
	while (cmd->heredoc[cmd->i_hd])
	{
		if (heredoc_2(cmd, ppl) != 0)
			j++;
		if (ppl->error != 0)
			return (1);
		cmd->i_hd++;
	}
	return (j);
}
