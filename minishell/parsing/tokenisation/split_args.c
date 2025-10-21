/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:24:21 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 14:43:29 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*extract_word(const char *str, int *i, t_hub *hub)
{
	int		start;
	char	*word;
	char	*tmp;

	start = *i;
	move_until_word_end(str, i);
	word = ft_substr(str, start, *i - start);
	if (!word)
		return (NULL);
	tmp = expand_vars_with_quotes(word, hub);
	if (tmp)
	{
		free(word);
		word = remove_quotes(tmp);
		free(tmp);
	}
	return (word);
}

char	*extract_operator(const char *str, int *i, t_hub *hub)
{
	int	start;

	start = *i;
	(void)hub;
	if (str[*i] == '>' && str[*i + 1] == '>')
		*i += 2;
	else if (str[*i] == '<' && str[*i + 1] == '<')
		*i += 2;
	else
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
