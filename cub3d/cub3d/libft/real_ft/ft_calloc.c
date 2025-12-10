/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:41:28 by cade-jes          #+#    #+#             */
/*   Updated: 2025/05/28 11:22:25 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*str;

	if (size != 0 && nmemb > ((size_t) -1 / size))
		return (NULL);
	str = malloc(size * nmemb);
	if (!str)
		return (NULL);
	i = 0;
	if (size == 0)
		str[i] = 0;
	while (i < size * nmemb)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}
