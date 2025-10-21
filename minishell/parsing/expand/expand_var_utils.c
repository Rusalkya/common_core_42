/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 10:07:35 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_special_var(t_expand *exp)
{
	if (exp->buffer[exp->i + 1] == '?')
	{
		exp->value = ft_itoa(exp->hub->last_value);
		exp->j = exp->i;
		exp->i += 2;
		return (1);
	}
	else if (exp->buffer[exp->i + 1] == '$')
	{
		exp->value = ft_itoa(getpid());
		exp->j = exp->i;
		exp->i += 2;
		return (1);
	}
	else if (exp->buffer[exp->i + 1] == '@')
	{
		exp->value = ft_strdup("");
		exp->j = exp->i;
		exp->i += 2;
		return (1);
	}
	return (0);
}

int	expand_special_vars(t_expand *exp)
{
	char	*tmp;

	if (!handle_special_var(exp))
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
