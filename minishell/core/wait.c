/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:18:02 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 14:19:03 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_signal_msg(int status)
{
	int	s;

	if (!WIFSIGNALED(status))
		return ;
	s = WTERMSIG(status);
	if (s == SIGINT)
		ft_printf(2, "\n");
	else if (s == SIGQUIT)
		ft_printf(2, "Quit (core dumped)\n");
}

static int	code_from_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	ft_wait_2(int left, pid_t last)
{
	int		status;
	int		exit_code;
	pid_t	r;

	while (left > 0)
	{
		r = waitpid(-1, &status, 0);
		if (r == -1 && errno == EINTR)
			continue ;
		if (r == -1)
			break ;
		if (r == last)
		{
			print_signal_msg(status);
			exit_code = code_from_status(status);
		}
		left--;
	}
	return (exit_code);
}

int	ft_wait(t_hub *hub, t_ppl *ppl)
{
	int		left;
	int		exit_code;
	pid_t	last;

	if (ppl->i_pd <= 0)
		return (pipeline_end(hub, ppl->error), sig_inter(), 0);
	last = ppl->lst_pid[ppl->i_pd - 1];
	exit_code = 0;
	left = ppl->i_pd;
	exit_code = ft_wait_2(left, last);
	pipeline_end(hub, ppl->error);
	return (sig_inter(), exit_code);
}
