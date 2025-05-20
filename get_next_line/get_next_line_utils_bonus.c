/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:37:23 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/19 14:39:20 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	a;
	size_t	b;

	if (!s1)
		return (ft_strdup(s2));
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	res = ft_calloc(a + b + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < a)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < b)
		res[i++] = s2[j++];
	free(s1);
	return (res);
}

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
