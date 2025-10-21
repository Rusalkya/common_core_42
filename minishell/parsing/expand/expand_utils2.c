/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:30:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 10:07:35 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_var_value(char *var, t_hub *hub)
{
	char	*value;

	if (!var)
		return (NULL);
	if (ft_strcmp(var, "?") == 0)
		return (ft_itoa(hub->last_value));
	if (ft_strcmp(var, "$") == 0)
		return (ft_itoa(getpid()));
	value = ft_getenv(hub, hub->info, var);
	if (value)
		return (value);
	return (ft_strdup(""));
}

char	*replace_var(t_expand *exp)
{
	char	*new_buffer;
	size_t	prefix_len;
	size_t	value_len;
	size_t	suffix_len;
	size_t	total_len;

	prefix_len = exp->j;
	value_len = ft_strlen(exp->value);
	suffix_len = ft_strlen(exp->buffer + exp->i);
	total_len = prefix_len + value_len + suffix_len + 1;
	new_buffer = malloc(total_len);
	if (!new_buffer)
		return (NULL);
	if (prefix_len > 0)
		ft_strlcpy(new_buffer, exp->buffer, prefix_len + 1);
	else
		new_buffer[0] = '\0';
	ft_strlcat(new_buffer, exp->value, total_len);
	ft_strlcat(new_buffer, exp->buffer + exp->i, total_len);
	return (new_buffer);
}

int	handle_quotes(char c, int quote_state)
{
	if (c == '\'' && quote_state == 0)
		return (1);
	else if (c == '\'' && quote_state == 1)
		return (0);
	else if (c == '\"' && quote_state == 0)
		return (2);
	else if (c == '\"' && quote_state == 2)
		return (0);
	return (quote_state);
}

int	process_var(t_expand *exp)
{
	int	start;
	int	len;

	start = exp->i + 1;
	len = 0;
	while (exp->buffer[start + len] && (ft_isalnum(exp->buffer[start + len])
			|| exp->buffer[start + len] == '_'))
		len++;
	exp->var = ft_substr(exp->buffer, start, len);
	if (!exp->var)
		return (-1);
	exp->value = get_var_value(exp->var, exp->hub);
	if (!exp->value)
	{
		free(exp->var);
		return (-1);
	}
	exp->j = exp->i;
	free(exp->var);
	return (start + len);
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
