/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 00:00:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 21:07:50 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_var_expansion(t_expand *exp)
{
	if (expand_special_vars(exp))
		return (1);
	else if (exp->buffer[exp->i + 1]
		&& is_valid_var_char(exp->buffer[exp->i + 1]))
	{
		if (!expand_regular_var(exp))
			return (0);
		return (1);
	}
	else
	{
		exp->i++;
		return (1);
	}
}
