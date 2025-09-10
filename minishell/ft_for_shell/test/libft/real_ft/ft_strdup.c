/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:00:53 by cade-jes          #+#    #+#             */
/*   Updated: 2025/08/14 16:27:29 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	size_t	i;

	dst = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i <= ft_strlen(s))
	{
		dst[i] = s[i];
		i++;
	}
	return (dst);
}
