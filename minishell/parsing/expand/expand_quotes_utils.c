/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_quotes_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:45:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 10:07:35 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*process_special_var(char *buffer, int *i, t_hub *hub)
{
	char	*var_value;

	if (buffer[*i + 1] == '?')
	{
		var_value = ft_itoa(hub->last_value);
		*i += 2;
	}
	else if (buffer[*i + 1] == '$')
	{
		var_value = ft_itoa(getpid());
		*i += 2;
	}
	else if (buffer[*i + 1] == '@')
	{
		var_value = ft_strdup("");
		*i += 2;
	}
	else
		return (NULL);
	return (var_value);
}

char	*process_regular_var(char *buffer, int *i, t_hub *hub)
{
	char	*var_name;
	char	*var_value;
	int		var_start;
	int		var_len;

	var_start = *i + 1;
	var_len = 0;
	while (buffer[var_start + var_len]
		&& (ft_isalnum(buffer[var_start + var_len])
			|| buffer[var_start + var_len] == '_'))
		var_len++;
	var_name = ft_substr(buffer, var_start, var_len);
	var_value = get_var_value(var_name, hub);
	free(var_name);
	*i = var_start + var_len;
	return (var_value);
}
