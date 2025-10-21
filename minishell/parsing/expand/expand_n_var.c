/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_n_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:40:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 21:07:50 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	expand_regular_var(t_expand *exp)
{
	char	*tmp;

	exp->i = process_var(exp);
	if (exp->i == -1)
		return (0);
	tmp = replace_var(exp);
	if (!tmp)
		return (0);
	free(exp->buffer);
	exp->buffer = tmp;
	exp->i = exp->j + ft_strlen(exp->value);
	free(exp->value);
	return (1);
}

static int	handle_dollar_sign(t_expand *exp, int quote_state)
{
	if (exp->buffer[exp->i] == '$' && quote_state != 1)
	{
		if (exp->buffer[exp->i + 1] && (is_valid_var_char(exp->buffer[exp->i
						+ 1]) || exp->buffer[exp->i + 1] == '?'
				|| exp->buffer[exp->i + 1] == '$'))
			return (handle_var_expansion(exp));
		else
		{
			exp->i++;
			return (1);
		}
	}
	exp->i++;
	return (1);
}

int	expand_variables(t_expand *exp)
{
	int	quote_state;

	quote_state = 0;
	exp->i = 0;
	while (exp->buffer[exp->i])
	{
		quote_state = handle_quotes(exp->buffer[exp->i], quote_state);
		if (!handle_dollar_sign(exp, quote_state))
			return (0);
	}
	return (1);
}

static int	init_expansion(t_expand *exp, char *buffer, t_hub *hub)
{
	char	*tmp;

	tmp = ft_strdup(buffer);
	if (!tmp)
		return (0);
	exp->buffer = tmp;
	exp->hub = hub;
	exp->gc = hub->gc;
	exp->i = 0;
	exp->is_pid = 0;
	return (1);
}

char	*expand_vars(char *buffer, t_hub *hub)
{
	t_expand	exp;

	if (!buffer)
		return (NULL);
	if (!init_expansion(&exp, buffer, hub))
		return (NULL);
	if (!expand_variables(&exp))
	{
		free(exp.buffer);
		return (NULL);
	}
	return (exp.buffer);
}
