/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:30:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 10:07:35 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*extract_quoted_content(const char *str, int *i, char quote_char)
{
	int		start;
	int		len;
	char	*result;

	start = *i;
	(*i)++;
	while (str[*i] && str[*i] != quote_char)
		(*i)++;
	if (!str[*i])
		return (NULL);
	len = *i - start;
	result = ft_substr(str, start, len);
	(*i)++;
	return (result);
}

static void	copy_quoted_content(char *str, int *i, int *j, char *result)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		result[(*j)++] = str[(*i)++];
	if (str[*i] == quote)
		(*i)++;
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			copy_quoted_content(str, &i, &j, result);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
