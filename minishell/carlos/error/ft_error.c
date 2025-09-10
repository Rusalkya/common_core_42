/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:46:33 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/14 14:40:53 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

void	ft_error(const char *str, const char *error)
{
	if (error)
		ft_printf(2, "minishell: %s: %s\n", str, error);
	else
		ft_printf(2, "minishell: error: %s\n", str);
}
