/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-jes <cade-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:45:34 by cade-jes          #+#    #+#             */
/*   Updated: 2025/10/16 11:20:40 by cade-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if ((s1[i] == '=' || s1[i] == 0) && (s2[i] == '=' || s2[i] == 0))
		return (0);
	if (s2[i] == '=')
		return (1);
	if (s1[i] == '=')
		return (-1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	does_it_exist(t_info *info, char *src)
{
	int	i;

	i = 0;
	if (!info->exp)
		return (1);
	while (info->exp[i])
	{
		if (ft_strcmp_equal(src, info->exp[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_getenv(t_hub *hub, t_info *info, char *str)
{
	int		i;
	int		j;
	int		v;
	char	*dst;

	if (!info || !info->env)
		return (NULL);
	i = 0;
	while (info->env[i] && ft_strcmp_equal(str, info->env[i]) != 0)
		i++;
	if (!info->env[i])
		return (NULL);
	j = 0;
	while (info->env[i][j] != '=')
		j++;
	dst = malloc(ft_strlen(info->env[i]) - j + 2);
	if (!dst)
		return (ft_exit(hub, 1), NULL);
	v = 0;
	while (info->env[i][++j])
	{
		dst[v] = info->env[i][j];
		v++;
	}
	return (dst[v] = 0, dst);
}
