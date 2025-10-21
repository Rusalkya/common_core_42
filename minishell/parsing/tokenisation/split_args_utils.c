/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:15:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 16:02:28 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_next_token(char *input, int *i, t_hub *hub)
{
	char	*token;

	if (is_operator_char(input[*i]))
		token = extract_operator(input, i, hub);
	else
		token = extract_word(input, i, hub);
	return (token);
}

void	move_until_word_end(const char *s, int *i)
{
	char	q;

	q = 0;
	while (s[*i])
	{
		if (!q && (s[*i] == '\'' || s[*i] == '"'))
		{
			q = s[*i];
			(*i)++;
		}
		else if (q && s[*i] == q)
		{
			q = 0;
			(*i)++;
		}
		else if (!q && ((s[*i] >= 9 && s[*i] <= 13) || s[*i] == 32
				|| is_operator_char(s[*i])))
			break ;
		else
			(*i)++;
	}
}

static char	**process_input_splitting(char *input, t_hub *hub)
{
	char	**result;
	char	*token;
	int		i;
	int		count;

	result = NULL;
	i = 0;
	count = 0;
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		token = get_next_token(input, &i, hub);
		if (token)
			result = realloc_tab(result, token, count++, hub);
	}
	return (result);
}

char	**enhanced_split_command(char *input, t_hub *hub)
{
	char	**result;

	if (!input)
		return (NULL);
	if (!validate_buffer_syntax(input))
		return (NULL);
	result = process_input_splitting(input, hub);
	if (!validate_string_tokens(result, hub))
	{
		free_str_tab(result);
		return (NULL);
	}
	return (result);
}
