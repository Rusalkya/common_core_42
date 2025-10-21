/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 14:00:00 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_whitespace(char *input, int *i)
{
	while ((input[*i] >= 9 && input[*i] <= 13) || input[*i] == 32)
		(*i)++;
}

static bool	is_redirection_string(char *token)
{
	return (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}

static void	print_syntax_error_newline(t_hub *hub)
{
	hub->ppl->error = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putstr_fd("`newline'\n", 2);
}

static void	print_syntax_error_token(char *token, t_hub *hub)
{
	hub->ppl->error = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

bool	validate_string_tokens(char **tokens, t_hub *hub)
{
	int	i;

	if (!tokens)
		return (false);
	i = 0;
	while (tokens[i])
	{
		if (is_redirection_string(tokens[i]))
		{
			if (!tokens[i + 1])
			{
				print_syntax_error_newline(hub);
				return (false);
			}
			if (is_redirection_string(tokens[i + 1]))
			{
				print_syntax_error_token(tokens[i + 1], hub);
				return (false);
			}
		}
		i++;
	}
	return (true);
}
