/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init_parsing_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 10:47:57 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quote_in_split(const char *input, int *i, char *quote)
{
	if (!*quote && (input[*i] == '\'' || input[*i] == '"'))
		*quote = input[*i];
	else if (*quote && input[*i] == *quote)
		*quote = 0;
}

int	count_pipeline_parts(const char *input)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 1;
	quote = 0;
	while (input[i])
	{
		if (!quote && (input[i] == '\'' || input[i] == '"'))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		else if (!quote && input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

void	extract_pipeline_parts(const char *input, char **result)
{
	int		vars[2];
	int		start;
	char	quote;

	vars[0] = 0;
	start = 0;
	vars[1] = 0;
	quote = 0;
	while (input[vars[0]])
	{
		if (!quote && (input[vars[0]] == '\'' || input[vars[0]] == '"'))
			quote = input[vars[0]];
		else if (quote && input[vars[0]] == quote)
			quote = 0;
		else if (!quote && input[vars[0]] == '|')
		{
			handle_pipe_extraction(input, result, vars, &start);
			continue ;
		}
		vars[0]++;
	}
	if (vars[0] > start)
		result[vars[1]++] = ft_substr(input, start, vars[0] - start);
	result[vars[1]] = NULL;
}

void	skip_whitespace_in_parsing(char **tokens, int *i)
{
	while (tokens[*i] && (ft_strcmp(tokens[*i], " ") == 0
			|| ft_strcmp(tokens[*i], "\t") == 0))
		(*i)++;
}

int	count_pipeline_commands(const char *input)
{
	int		count;
	int		i;
	char	quote;

	count = 1;
	i = 0;
	quote = 0;
	while (input[i])
	{
		handle_quote_in_split(input, &i, &quote);
		if (!quote && input[i] == '|')
			count++;
		i++;
	}
	return (count);
}
