/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:46:33 by cade-jes          #+#    #+#             */
/*   Updated: 2025/09/11 12:07:58 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(const char *str, const char *error)
{
	if (error)
		ft_printf(2, "minishell: %s: %s\n", str, error);
	else
		ft_printf(2, "minishell: error: %s\n", str);
}
