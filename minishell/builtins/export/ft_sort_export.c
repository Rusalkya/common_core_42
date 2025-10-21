/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:02:40 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/01 13:30:57 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sort_export(t_info *info)
{
	int		i;
	int		j;
	char	*swap;

	j = 0;
	while (info->exp[j])
	{
		i = 0;
		while (info->exp[i + 1])
		{
			if (ft_strcmp_equal(info->exp[i], info->exp[i + 1]) > 0)
			{
				swap = info->exp[i];
				info->exp[i] = info->exp[i + 1];
				info->exp[i + 1] = swap;
			}
			i++;
		}
		j++;
	}
}
