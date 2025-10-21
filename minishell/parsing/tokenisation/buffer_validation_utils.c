/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_validation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 10:07:35 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_quoted_arg(char *buffer, int *j)
{
	char	quote;

	quote = buffer[*j];
	(*j)++;
	while (buffer[*j] && buffer[*j] != quote)
		(*j)++;
	if (buffer[*j] == quote)
		return (1);
	return (0);
}

int	has_valid_filename(char *buffer, int start_pos)
{
	int	j;

	j = start_pos;
	if (!buffer[j])
		return (0);
	if (buffer[j] == '"' || buffer[j] == '\'')
		return (check_quoted_arg(buffer, &j));
	if (buffer[j] != '>' && buffer[j] != '<' && buffer[j] != '|')
		return (1);
	return (0);
}

void	advance_past_redirect(char *buffer, int *i)
{
	char	current;
	char	next;

	current = buffer[*i];
	next = buffer[*i + 1];
	if ((current == '>' && next == '>') || (current == '<' && next == '<'))
		(*i)++;
	(*i)++;
	while (buffer[*i] && (buffer[*i] == ' ' || buffer[*i] == '\t'))
		(*i)++;
}

int	skip_initial_spaces(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] == ' ' || buffer[i] == '\t')
		i++;
	return (i);
}

int	check_pipe_at_start(char *buffer)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	(void)buffer;
	return (0);
}
