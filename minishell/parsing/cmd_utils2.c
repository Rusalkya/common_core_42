/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 21:07:50 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_cmd_structure(t_cmd *cmd, char *command)
{
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup(command);
	cmd->args[1] = NULL;
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	cmd->heredoc = NULL;
	cmd->i_hd = 0;
	cmd->std_in = 1;
	cmd->i = 0;
}

void	parse_command_simplified(char *input, t_cmd *cmd, t_hub *hub)
{
	char	**tokens;
	char	*command;

	tokens = enhanced_split_command(input, hub);
	if (!tokens)
		return ;
	command = find_command_in_tokens(tokens);
	if (command)
		init_cmd_structure(cmd, command);
	parse_redirections(tokens, cmd, hub);
	if (command)
		process_tokens(cmd, tokens);
	free_str_tab(tokens);
}
