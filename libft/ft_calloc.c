/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:58:47 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/01 13:37:20 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*cal;
	size_t			t;
	size_t			i;

	i = 0;
	t = nmemb * size;
	cal = malloc(t);
	if (!cal)
		return (NULL);
	while (i < t)
	{
		cal[i] = 0;
		i++;
	}
	return ((void *)cal);
}
