/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:15:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/14 15:26:11 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_only_empty_quotes(char *buffer)
{
	int	i;
	int	found_content;

	i = 0;
	found_content = 0;
	while (buffer[i])
	{
		if (buffer[i] != '"' && buffer[i] != '\'' && !ft_isspace(buffer[i]))
			found_content = 1;
		i++;
	}
	return (!found_content);
}

int	check_quote_closure(char *buffer, int *i)
{
	char	quote;

	quote = buffer[*i];
	(*i)++;
	while (buffer[*i] && buffer[*i] != quote)
		(*i)++;
	if (!buffer[*i])
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (0);
	}
	return (1);
}

int	validate_quotes(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '"' || buffer[i] == '\'')
		{
			if (!check_quote_closure(buffer, &i))
				return (0);
		}
		i++;
	}
	return (1);
}
