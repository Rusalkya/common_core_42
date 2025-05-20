/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:35:22 by clfouger          #+#    #+#             */
/*   Updated: 2025/05/20 14:08:34 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

char	*getl(char *sbuffer)
{
	int		i;
	int		j;
	char	*line;

	if (!sbuffer || !*sbuffer)
		return (NULL);
	i = 0;
	while (sbuffer[i] && sbuffer[i] != '\n')
		i++;
	line = ft_calloc(i + (sbuffer[i] == '\n') + 1, sizeof(char));
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = sbuffer[j];
	if (sbuffer[i] == '\n')
		line[j++] = '\n';
	return (line);
}

char	*get_rest(char *sbuffer)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (sbuffer[i] && sbuffer[i] != '\n')
		i++;
	if (!sbuffer[i])
		return (free(sbuffer), NULL);
	rest = ft_calloc(ft_strlen(sbuffer) - i, sizeof(char));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (sbuffer[i])
	{
		rest[j] = sbuffer[i];
		i++;
		j++;
	}
	free(sbuffer);
	return (rest);
}

char	*gnl_free(char **sbuffer)
{
	free(*sbuffer);
	*sbuffer = NULL;
	return (NULL);
}

char	*gnl_error(char **sbuffer, char *temp)
{
	free(temp);
	if (sbuffer)
	{
		free(*sbuffer);
		*sbuffer = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*sbuffer[FOPEN_MAX];
	char		*temp;
	char		*line;
	ssize_t		bytes_read;

	if ((fd < 0) || (BUFFER_SIZE < 0))
		return (NULL);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(sbuffer[fd], '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (gnl_error(&sbuffer[fd], temp));
		temp[bytes_read] = '\0';
		sbuffer[fd] = ft_strjoin(sbuffer[fd], temp);
	}
	free(temp);
	if (!sbuffer[fd] || !*sbuffer[fd])
		return (gnl_free(&sbuffer[fd]));
	line = getl(sbuffer[fd]);
	sbuffer[fd] = get_rest(sbuffer[fd]);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	printf("Ligne lue : %s", line);
	free(line);
	line = get_next_line(fd);
	printf("Ligne lue : %s", line);
	free(line);
	line = get_next_line(fd);
	printf("Ligne lue : %s", line);
	free(line);
	close(fd);
	return (0);
}
*/