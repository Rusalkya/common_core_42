/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:35:24 by cade-jes          #+#    #+#             */
/*   Updated: 2025/09/10 13:32:59 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_realloc(char **ptr, int size)
{
	int		i;
	char	*dst;

	dst = ft_calloc(1, size + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while ((*ptr)[i] && i < size)
	{
		dst[i] = (*ptr)[i];
		i++;
	}
	free(*ptr);
	*ptr = NULL;
	return (dst);
}
