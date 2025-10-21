/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:24:10 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 17:29:23 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	process_input(char *input, t_hub *hub)
{
	if (input[0] == 0)
		return ;
	hub->cmd = parse_pipeline(input, hub);
	if (!hub->cmd || hub->ppl->error != 0)
	{
		hub->ppl->error = 0;
		hub->last_value = 2;
		free_cmd(hub->cmd);
		return ;
	}
	hub->last_value = pipeline(hub);
	hub->ppl->error = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_hub	*hub;
	char	*input;

	if (argc > 1)
		return (ft_error("too many arguments", NULL), 2);
	(void)argv;
	sig_inter();
	hub = creat_hub(envp);
	while (1)
	{
		input = read_input(hub);
		if (!input)
			ft_exit(hub, hub->last_value);
		process_input(input, hub);
	}
	ft_exit(hub, hub->last_value);
	return (0);
}
