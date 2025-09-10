/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 01:13:15 by cade-jes          #+#    #+#             */
/*   Updated: 2025/05/28 02:14:23 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

static char	*finalizer(char **buf, char *str, int probleme)
{
	if (!str || probleme == 0)
	{
		free(*buf);
		*buf = NULL;
	}
	if (!str || (probleme == 0 && str[0] == '\0'))
	{
		free(str);
		return (NULL);
	}
	return (str);
}

static void	suppre(char *reading)
{
	int	i;

	i = 0;
	while (reading[i])
	{
		reading[i] = 0;
		i++;
	}
}

static char	*find_new_line(char *reading, char *str, int *probleme, int fd)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == BUFFER_SIZE)
		{
			str = ft_strjoin_gnl(str, reading);
			suppre(reading);
			*probleme = read(fd, reading, BUFFER_SIZE);
			if (*probleme == -1 || !str)
			{
				free(str);
				return (NULL);
			}
			if (*probleme == 0)
				return (str);
			i = 0;
		}
		if (reading[i] == '\n')
			str = ft_strjoin_gnl(str, reading);
		if (reading[i] == '\n')
			return (str);
		i++;
	}
}

static char	*preparation(char **buf, int fd)
{
	int		probleme;
	char	*reading;

	probleme = 1;
	reading = calloc_char(BUFFER_SIZE + 1);
	if (!reading)
		return (NULL);
	if (*buf != NULL)
		ft_strcpy(reading, *buf);
	else
	{
		probleme = read(fd, reading, BUFFER_SIZE);
		if (probleme == -1 || probleme == 0)
		{
			free(*buf);
			free(reading);
			return (NULL);
		}
	}
	return (reading);
}

char	*get_next_line(int fd)
{
	static char	*buf[1024] = {NULL};
	char		*reading;
	char		*str;
	int			probleme;

	if (fd < 0 || fd >= 1024)
		return (NULL);
	probleme = 1;
	reading = preparation(&buf[fd], fd);
	if (!reading)
		return (NULL);
	str = calloc_char(1);
	if (!str)
		return (NULL);
	str = find_new_line(reading, str, &probleme, fd);
	if (str && probleme > 0)
		ft_strchr_gnl(&buf[fd], reading);
	free(reading);
	return (finalizer(&buf[fd], str, probleme));
}
