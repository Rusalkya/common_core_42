/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:31:51 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/13 14:29:33 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_hub *hub, int i)
{
	if (hub == NULL)
		exit(i);
	rl_clear_history();
	if (hub->info)
		free_info(hub->info);
	if (hub->cmd)
		free_cmd(hub->cmd);
	if (hub->ppl)
		free_ppl(hub->ppl);
	if (hub->token)
		free_token(hub->token);
	if (hub->rl)
		free_rl(hub->rl);
	if (hub->quote)
		free(hub->quote);
	free(hub);
	exit(i);
}
