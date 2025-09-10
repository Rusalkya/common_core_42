/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:13:06 by cade-jes          #+#    #+#             */
/*   Updated: 2025/05/28 09:14:09 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

char	*calloc_char(size_t size)
{
	char	*str;
	size_t	i;

	str = malloc(size + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

void	ft_strchr_gnl(char **buf, char *reading)
{
	long	i;
	long	j;

	i = 0;
	j = 0;
	while (reading[i])
	{
		if (reading[i] == '\n')
		{
			i++;
			if (*buf != NULL)
				free(*buf);
			*buf = calloc_char(ft_strlen(&reading[i]) + 1);
			if (!(*buf))
				return ;
			while (reading[i + j])
			{
				(*buf)[j] = reading[i + j];
				j++;
			}
			return ;
		}
		i++;
	}
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	dst = calloc_char(ft_strlen(s1) + ft_strlen(s2));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && s2[j] != '\n')
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	if (s2[j] == '\n')
		dst[i++] = '\n';
	dst[i] = 0;
	free(s1);
	return (dst);
}
