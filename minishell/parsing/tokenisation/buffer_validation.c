/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:20:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/15 18:56:42 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_syntax_error(char *buffer, int *i)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (!buffer[*i])
		ft_putstr_fd("`newline'\n", 2);
	else
	{
		ft_putstr_fd("`", 2);
		ft_putchar_fd(buffer[*i], 2);
		ft_putstr_fd("'\n", 2);
	}
	return (0);
}

int	handle_pipe_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	return (0);
}

int	check_redir_syntax(char *buffer, int *i)
{
	int	j;

	if (buffer[*i] == '>' || buffer[*i] == '<')
	{
		advance_past_redirect(buffer, i);
		j = *i;
		if (!has_valid_filename(buffer, j))
			return (handle_syntax_error(buffer, i));
		*i = j;
		while (buffer[*i] && buffer[*i] != ' ' && buffer[*i] != '\t'
			&& buffer[*i] != '>' && buffer[*i] != '<' && buffer[*i] != '|')
		{
			if (buffer[*i] == '"' || buffer[*i] == '\'')
			{
				if (!check_quote_closure(buffer, i))
					return (0);
			}
			(*i)++;
		}
	}
	return (1);
}

int	check_pipe_syntax(char *buffer, int *i)
{
	if (buffer[*i] == '|')
	{
		(*i)++;
		while (buffer[*i] && (buffer[*i] == ' ' || buffer[*i] == '\t'))
			(*i)++;
		if (!buffer[*i])
			return (handle_syntax_error(buffer, i));
		if (buffer[*i] == '|')
			return (handle_pipe_error());
	}
	return (1);
}

int	validate_buffer_syntax(char *buffer)
{
	int	i;

	i = skip_initial_spaces(buffer);
	if (buffer[i] == '|')
		return (check_pipe_at_start(buffer));
	while (buffer[i])
	{
		if (!process_buffer_char(buffer, &i))
			return (0);
	}
	return (1);
}
