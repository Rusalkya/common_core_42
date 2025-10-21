/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enhanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:10:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 16:02:28 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**process_input_tokens(char *input, t_hub *hub)
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
	result = process_input_tokens(input, hub);
	if (!validate_string_tokens(result, hub))
	{
		free_str_tab(result);
		return (NULL);
	}
	return (result);
}
