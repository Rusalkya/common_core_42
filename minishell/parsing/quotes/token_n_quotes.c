/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:57:31 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/09 14:04:40 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_quoted(const char *str, int *i, t_quote_type *quote_type)
{
	char	quote;
	int		start;
	char	*res;

	quote = str[*i];
	start = ++(*i);
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] != quote)
		return (NULL);
	if (quote == '\'')
		*quote_type = SINGLE_QUOTE;
	else
		*quote_type = DOUBLE_QUOTE;
	res = ft_substr(str, start, *i - start);
	(*i)++;
	return (res);
}

char	*extract_unquoted(const char *str, int *i)
{
	int		start;
	char	*res;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\''
		&& str[*i] != '"')
		(*i)++;
	if (*i == start)
		return (NULL);
	res = ft_substr(str, start, *i - start);
	return (res);
}

t_token	*create_token(char *str, t_quote_type quote_type, t_hub *hub)
{
	t_token	*token;

	token = lst_new_token(str, WORD, hub);
	if (!token)
		return (NULL);
	token->quote = quote_type;
	return (token);
}

static t_token	*create_and_add_token(const char *line, int *i, t_token **last,
		t_hub *hub)
{
	t_quote_type	quote;
	char			*token;
	t_token			*new;

	quote = NO_QUOTE;
	token = NULL;
	if (line[*i] == '\'' || line[*i] == '"')
		token = extract_quoted(line, i, &quote);
	else
		token = extract_unquoted(line, i);
	if (!token)
		return (NULL);
	new = create_token(token, quote, hub);
	if (*last)
		(*last)->next = new;
	*last = new;
	return (new);
}

t_token	*parse_tokens_with_quotes(const char *line, t_hub *hub)
{
	int		i;
	t_token	*head;
	t_token	*last;
	t_token	*new;

	i = 0;
	head = NULL;
	last = NULL;
	while (line[i])
	{
		new = create_and_add_token(line, &i, &last, hub);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
	}
	return (head);
}
