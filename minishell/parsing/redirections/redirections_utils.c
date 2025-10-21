/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clfouger <clfouger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:35:00 by clfouger          #+#    #+#             */
/*   Updated: 2025/10/16 13:30:49 by clfouger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**realloc_tab_2(char **old, char *new_str, int count, t_hub *hub)
{
	char	**new;
	int		i;

	(void)hub;
	new = malloc(sizeof(char *) * (count + 2));
	if (!new)
		return (ft_error("realloc tab", strerror(errno)), NULL);
	i = 0;
	while (i < count && old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = ft_strdup(new_str);
	new[i + 1] = NULL;
	if (old)
		free(old);
	return (new);
}
