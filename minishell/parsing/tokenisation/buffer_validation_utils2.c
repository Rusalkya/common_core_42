/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_validation_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:40:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 12:03:43 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_buffer_char(char *buffer, int *i)
{
	if (buffer[*i] == '"' || buffer[*i] == '\'')
	{
		if (!check_quote_closure(buffer, i))
			return (0);
		(*i)++;
	}
	else if (buffer[*i] == '|')
	{
		if (buffer[*i + 1] == '|')
			return (0);
		(*i)++;
		while (buffer[*i] == ' ' || buffer[*i] == '\t')
			(*i)++;
		if (!buffer[*i] || buffer[*i] == '|')
			return (0);
	}
	else
		(*i)++;
	return (1);
}
