/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:02:38 by clfouger          #+#    #+#             */
/*   Updated: 2025/11/27 17:49:56 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	*trim_string(char *str)
{
	char	*trimmed;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);
	ft_strcpy(trimmed, str);
	while (len > 0 && (trimmed[len - 1] == '\n' || trimmed[len - 1] == '\r'
			|| trimmed[len - 1] == ' ' || trimmed[len - 1] == '\t'))
	{
		trimmed[len - 1] = '\0';
		len--;
	}
	return (trimmed);
}

static int	return_nbr(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	skip_whitespace(&str);
	nbr = ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	skip_whitespace(&str);
	if (*str == ',' || *str == '\n' || *str == '\0')
		return (nbr);
	return (-1);
}

static int	parse_rgb_values(char *trimmed, int *r, int *g, int *b)
{
	char	*ptr;
	int		i;

	ptr = trimmed;
	*r = return_nbr(ptr);
	ptr = ft_strchr(ptr, ',');
	*g = return_nbr(ptr + 1);
	ptr = ft_strchr(ptr + 1, ',');
	*b = return_nbr(ptr + 1);
	i = 1;
	while (ptr[i] && ptr[i] != '\n')
	{
		if (ptr[i] == ',')
			return (-1);
		i++;
	}
	return (0);
}

int	get_color(t_hub *hub, char *str)
{
	char	*trimmed;
	int		r;
	int		g;
	int		b;

	(void)hub;
	if (!str)
		return (-1);
	trimmed = trim_string(str);
	if (!trimmed)
		return (-1);
	if (parse_rgb_values(trimmed, &r, &g, &b) < 0)
	{
		free(trimmed);
		return (-1);
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free(trimmed);
		return (-1);
	}
	free(trimmed);
	return ((r << 16) | (g << 8) | b);
}
