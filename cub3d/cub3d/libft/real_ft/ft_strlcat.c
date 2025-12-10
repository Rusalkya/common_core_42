/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:48:43 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/14 16:27:24 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;

	i = 0;
	j = ft_strlen(dst);
	len_dst = j;
	if (siz != 0)
	{
		while (j < siz - 1 && src[i])
		{
			dst[j] = src[i];
			j++;
			i++;
		}
	}
	if (j < siz)
	{
		dst[j] = '\0';
		return (len_dst + ft_strlen(src));
	}
	return (siz + ft_strlen(src));
}
