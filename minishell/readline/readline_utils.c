/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:45:02 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/13 14:37:01 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_history(char *input)
{
	if (input && *input)
		add_history(input);
}

void	clear_current_line(void)
{
	printf("\r");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	cleanup_shell(t_rl *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	rl_clear_history();
}

void	handle_signal_interrupt(t_rl *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	clear_current_line();
}

void	execute_pipeline(t_hub *hub)
{
	pipeline(hub);
}
