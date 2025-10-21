/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:30:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 13:28:10 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_out	*create_output_redirect(char *filename, int type)
{
	t_out	*out;

	out = malloc(sizeof(t_out));
	if (!out)
		return (NULL);
	out->type = type;
	out->file = ft_strdup(filename);
	out->next = NULL;
	return (out);
}

void	add_output_redirect(t_cmd *cmd, t_out *new_out)
{
	t_out	*current;

	if (!cmd->file_out)
	{
		cmd->file_out = new_out;
	}
	else
	{
		current = cmd->file_out;
		while (current->next)
			current = current->next;
		current->next = new_out;
	}
}

int	handle_input_redirect(char **tokens, t_cmd *cmd, t_hub *hub,
		int *file_in_count)
{
	cmd->file_in = realloc_tab_2(cmd->file_in, tokens[1], *file_in_count, hub);
	(*file_in_count)++;
	cmd->std_in = 1;
	return (2);
}

int	handle_output_redirect(char **tokens, t_cmd *cmd, int type)
{
	t_out	*out;

	out = create_output_redirect(tokens[1], type);
	if (!out)
		return (0);
	add_output_redirect(cmd, out);
	return (2);
}

int	handle_heredoc_redirect(char **tokens, t_cmd *cmd, t_hub *hub)
{
	cmd->heredoc = realloc_tab_2(cmd->heredoc, tokens[1], cmd->i_hd, hub);
	cmd->i_hd++;
	cmd->std_in = 0;
	return (2);
}
