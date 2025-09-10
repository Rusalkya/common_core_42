/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:31:51 by cade-jes          #+#    #+#             */
/*   Updated: 2025/05/28 11:30:04 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*condition(void)
{
	char	*dst;

	dst = malloc(1);
	if (!dst)
		return (NULL);
	dst[0] = 0;
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*dst;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (condition());
	else if (len + start > ft_strlen(s))
		dst = malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	else
		dst = malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
