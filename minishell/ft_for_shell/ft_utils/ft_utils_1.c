/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:45:34 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/23 13:45:59 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_for_shell.h"

int	ft_strcmp_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if ((s1[i] == '=' || s1[i] == 0) && (s2[i] == '=' || s2[i] == 0))
		return (0);
	if (s2[i] == '=')
		return (1);
	if (s1[i] == '=')
		return (-1);
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
