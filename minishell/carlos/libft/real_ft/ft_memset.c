/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:03:24 by cade-jes          #+#    #+#             */
/*   Updated: 2025/05/28 11:22:48 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	char	*dst;

	dst = s;
	while (len)
	{
		*dst = (unsigned char)c;
		dst++;
		len--;
	}
	return (s);
}
