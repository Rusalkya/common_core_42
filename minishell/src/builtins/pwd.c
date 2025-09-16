/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:33:25 by cade-jes          #+#    #+#             */
/*   Updated: 2025/09/11 12:07:58 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
		return (path);
	ft_error("getcwd", strerror(errno));
	g_error = 1;
	return (NULL);
}
